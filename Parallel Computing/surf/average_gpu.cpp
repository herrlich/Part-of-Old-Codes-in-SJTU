#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <CL/opencl.h>
#include <time.h>
#include "responselayer.h"

static cl_command_queue queue = NULL;
static cl_context context = NULL;

static const int OCTAVES = 5;
static const int INTERVALS = 4;
static const float THRES = 0.001f;
static const int SAMPLE_STEP = 2;

const int filter_map[OCTAVES][INTERVALS] = { { 0, 1, 2, 3 },
{ 1, 3, 4, 5 },
{ 3, 5, 6, 7 },
{ 5, 7, 8, 9 },
{ 7, 9,10,11 } };

cl_mem cl_allocBuffer(size_t mem_size)
{
	cl_mem mem;
	cl_int status;
	static int allocationCount = 1;
	static size_t allocationSize = 0;
	allocationCount++;
	allocationSize += mem_size;
	mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY, mem_size, NULL, &status);
	if (status != CL_SUCCESS)checkErr(status);
	return mem;

}


// 读取图像数据，图像格式为4个十进制数字符表示一个14位的灰度值，之后接一个空格
void read_data(char* filename, int** data, int w, int h)
{
	FILE* pFile;

	pFile = fopen(filename, "r");

	*data = (int*)malloc(sizeof(int)*w * h);

	// get data
	int i, j;
	for (i = 0; i<w*h; i++)
	{
		fscanf(pFile, "%d ", &j);
		(*data)[i] = j;
		if (j == 0) printf("%d:%d ", i / 640, i % 640);
	}


	fclose(pFile);
}
void write_data_float_2(char * filename, float *data, int height, int width) {
	FILE *pFile;
	pFile = fopen(filename, "w");
	int i, j;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			fprintf(pFile, "%f ", data[i*width + j]);
		}
		fprintf(pFile, "\n");
	}
}
void write_data(char *filename, float2 *pixPos, float * det, int num) {
	FILE *pFile;
	pFile = fopen(filename, "w");
	int i;
	for (int i = 0; i < num; ++i) {
		fprintf(pFile, "%d,%d,%f\n", int(pixPos[i].x), int(pixPos[i].y), det[i]);
	}
}
void write_data_int(char* filename, int* data, int size)
{
	FILE* pFile;
	pFile = fopen(filename, "w");
	int i;
	for (i = 0; i<size; i++)
		fprintf(pFile, "%d ", data[i]);
	fclose(pFile);
}
void write_data_float(char* filename, float* data, int size)
{
	FILE* pFile;
	pFile = fopen(filename, "w");
	int i;
	for (i = 0; i<size; i++)
		fprintf(pFile, "%f ", data[i]);
	fclose(pFile);
}
void write_data_float2(char* filename, float2 * data, int size)
{
	FILE* pFile;
	pFile = fopen(filename, "w");
	int i;
	for (i = 0; i<size; i++)
		fprintf(pFile, "%f %f ", data[i].x, data[i].y);
	fclose(pFile);
}

//读取kernel文件
void read_source(char **data, size_t *length, char *filename)
{
	FILE *file;
	int len = 0;

	file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	*data = (char *)malloc(len + 1);
	fseek(file, 0, SEEK_SET);
	fread(*data, len, 1, file);
	(*data)[len] = 0;
	*length = len;

	printf("\ncheckpoint: read_source() success!\n");
}
void checkErr(cl_int err)
{
	printf("CL_ERROR: ");
	switch (err)
	{
	case CL_SUCCESS:
		printf("Success"); break;
	case CL_DEVICE_NOT_FOUND:
		printf("Device Not Found"); break;
	case CL_DEVICE_NOT_AVAILABLE:
		printf("Device Not Available"); break;
	case CL_COMPILER_NOT_AVAILABLE:
		printf("Compiler Not Available"); break;
	case CL_MEM_OBJECT_ALLOCATION_FAILURE:
		printf("Mem Object Allocation Failure"); break;
	case CL_OUT_OF_RESOURCES:
		printf("Out Of Resources"); break;
	case CL_OUT_OF_HOST_MEMORY:
		printf("Out Of Host Memory"); break;
	case CL_PROFILING_INFO_NOT_AVAILABLE:
		printf("Profiling Info Not Available"); break;
	case CL_MEM_COPY_OVERLAP:
		printf("Mem Copy Overlap"); break;
	case CL_IMAGE_FORMAT_MISMATCH:
		printf("Image Format Mismatch"); break;
	case CL_IMAGE_FORMAT_NOT_SUPPORTED:
		printf("Image Format Not Supported"); break;
	case CL_BUILD_PROGRAM_FAILURE:
		printf("Build Program Failure"); break;
	case CL_MAP_FAILURE:
		printf("Map Failure"); break;
	case CL_MISALIGNED_SUB_BUFFER_OFFSET:
		printf("Misaligned Sub Buffer Offset"); break;
	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
		printf("Exec Status Error For Events In Wait List"); break;
	case CL_INVALID_VALUE:
		printf("Invalid Value"); break;
	case CL_INVALID_DEVICE_TYPE:
		printf("Invalid Device Type"); break;
	case CL_INVALID_PLATFORM:
		printf("Invalid Platform"); break;
	case CL_INVALID_DEVICE:
		printf("Invalid Device"); break;
	case CL_INVALID_CONTEXT:
		printf("Invalid Context"); break;
	case CL_INVALID_QUEUE_PROPERTIES:
		printf("Invalid Queue Properties"); break;
	case CL_INVALID_COMMAND_QUEUE:
		printf("Invalid Command Queue"); break;
	case CL_INVALID_HOST_PTR:
		printf("Invalid Host Ptr"); break;
	case CL_INVALID_MEM_OBJECT:
		printf("Invalid Mem Object"); break;
	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
		printf("Invalid Image Format Descriptor"); break;
	case CL_INVALID_IMAGE_SIZE:
		printf("Invalid Image Size"); break;
	case CL_INVALID_SAMPLER:
		printf("Invalid Sampler"); break;
	case CL_INVALID_BINARY:
		printf("Invalid Binary"); break;
	case CL_INVALID_BUILD_OPTIONS:
		printf("Invalid Build Options"); break;
	case CL_INVALID_PROGRAM:
		printf("Invalid Program"); break;
	case CL_INVALID_PROGRAM_EXECUTABLE:
		printf("Invalid Program Executable"); break;
	case CL_INVALID_KERNEL_NAME:
		printf("Invalid kernel Name"); break;
	case CL_INVALID_KERNEL_DEFINITION:
		printf("Invalid Kernel Definition"); break;
	case CL_INVALID_KERNEL:
		printf("Invalid Kernel"); break;
	case CL_INVALID_ARG_INDEX:
		printf("Invalid Arg Index"); break;
	case CL_INVALID_ARG_VALUE:
		printf("Invalid Arg Value"); break;
	case CL_INVALID_ARG_SIZE:
		printf("Invalid Arg Size"); break;
	case CL_INVALID_KERNEL_ARGS:
		printf("Invalid Kernel Args"); break;
	case CL_INVALID_WORK_DIMENSION:
		printf("Invalid Work Dimension"); break;
	case CL_INVALID_WORK_GROUP_SIZE:
		printf("Invalid Work Group Size"); break;
	case CL_INVALID_WORK_ITEM_SIZE:
		printf("Invalid Work Item Size"); break;
	case CL_INVALID_GLOBAL_OFFSET:
		printf("Invalid Global Offset"); break;
	case CL_INVALID_EVENT_WAIT_LIST:
		printf("Invalid Event Wait List"); break;
	case CL_INVALID_EVENT:
		printf("Invalid Event"); break;
	case CL_INVALID_OPERATION:
		printf("Invalid Operation"); break;
	case CL_INVALID_GL_OBJECT:
		printf("Invalid GL Object"); break;
	case CL_INVALID_BUFFER_SIZE:
		printf("Invalid Buffer Size"); break;
	case CL_INVALID_MIP_LEVEL:
		printf("Invalid MIP Level"); break;
	case CL_INVALID_GLOBAL_WORK_SIZE:
		printf("Invalid Global Work Size"); break;
	case CL_INVALID_PROPERTY:
		printf("Invalid Property"); break;
	default:
		printf("Some Thing Wrong");
	}
	printf("\n");
	exit(0);
}

void createResponseMap(std::vector<ResponseLayer*> &responseMap, int octaves, int imgWidth, int imgHeight, int sample_step)
{

	int w = (imgWidth / sample_step);
	int h = (imgHeight / sample_step);
	int s = (sample_step);

	// Calculate approximated determinant of hessian values
	if (octaves >= 1)
	{
		responseMap.push_back(new ResponseLayer(w, h, s, 9));
		responseMap.push_back(new ResponseLayer(w, h, s, 15));
		responseMap.push_back(new ResponseLayer(w, h, s, 21));
		responseMap.push_back(new ResponseLayer(w, h, s, 27));
	}

	if (octaves >= 2)
	{
		responseMap.push_back(new ResponseLayer(w / 2, h / 2, s * 2, 39));
		responseMap.push_back(new ResponseLayer(w / 2, h / 2, s * 2, 51));
	}

	if (octaves >= 3)
	{
		responseMap.push_back(new ResponseLayer(w / 4, h / 4, s * 4, 75));
		responseMap.push_back(new ResponseLayer(w / 4, h / 4, s * 4, 99));
	}

	if (octaves >= 4)
	{
		responseMap.push_back(new ResponseLayer(w / 8, h / 8, s * 8, 147));
		responseMap.push_back(new ResponseLayer(w / 8, h / 8, s * 8, 195));
	}

	if (octaves >= 5)
	{
		responseMap.push_back(new ResponseLayer(w / 16, h / 16, s * 16, 291));
		responseMap.push_back(new ResponseLayer(w / 16, h / 16, s * 16, 387));
	}
}

void computeHessianDet(std::vector<ResponseLayer*> &responseMap, cl_mem d_intImage,
	int i_width, int i_height,
	cl_kernel hessian_det, cl_command_queue queue, cl_ulong & kernel_total)
{
	// set matrix size and x,y threads per block
	const int BLOCK_DIM = 16;
	cl_event event[100];
	cl_ulong kernel_begin, kernel_finish;
	size_t localWorkSize[2] = { BLOCK_DIM,BLOCK_DIM };
	size_t globalWorkSize[2];
	clSetKernelArg(hessian_det, 0, sizeof(cl_mem), (void *)&d_intImage);
	clSetKernelArg(hessian_det, 1, sizeof(cl_int), (void *)&i_width);
	clSetKernelArg(hessian_det, 2, sizeof(cl_int), (void *)&i_height);
	for (unsigned int i = 0; i < responseMap.size(); i++) {

		cl_mem responses = responseMap.at(i)->getResponses();
		cl_mem laplacian = responseMap.at(i)->getLaplacian();
		int step = responseMap.at(i)->getStep();
		int filter = responseMap.at(i)->getFilter();
		int layerWidth = responseMap.at(i)->getWidth();
		int layerHeight = responseMap.at(i)->getHeight();

		globalWorkSize[0] = roundUp(layerWidth, localWorkSize[0]);
		globalWorkSize[1] = roundUp(layerHeight, localWorkSize[1]);

		clSetKernelArg(hessian_det, 3, sizeof(cl_mem), (void*)&responses);
		clSetKernelArg(hessian_det, 4, sizeof(cl_mem), (void*)&laplacian);
		clSetKernelArg(hessian_det, 5, sizeof(int), (void*)&layerWidth);
		clSetKernelArg(hessian_det, 6, sizeof(int), (void*)&layerHeight);
		clSetKernelArg(hessian_det, 7, sizeof(int), (void*)&step);
		clSetKernelArg(hessian_det, 8, sizeof(int), (void*)&filter);

		clEnqueueNDRangeKernel(queue, hessian_det, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, &event[i]);

//		clGetEventProfilingInfo(event[i], CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &kernel_begin, NULL);
//		clGetEventProfilingInfo(event[i], CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &kernel_finish, NULL);
//		if (i == 0)printf("kernel time:%d %d\n", kernel_begin,kernel_finish);//kernel_total += kernel_begin;
//		if (i == 1)printf("kernel time:%d %d\n", kernel_begin,kernel_finish);
	}
//	printf("kernel_total:%d %d\n", kernel_begin, kernel_finish);
//	printf("kernel finish-begin:%d\n", kernel_finish - kernel_begin);
//	kernel_total += kernel_finish - kernel_begin;
//	printf("kernel of total:%d\n", kernel_total);
}

void selectIpoints(std::vector<ResponseLayer*> responseMap, cl_mem d_laplacian, cl_mem d_pixPos,
	cl_mem d_det, cl_kernel non_max_supression, cl_command_queue queue, cl_mem d_ipt_count, int octaves, float thres, cl_ulong & kernel_total)
{

	// The search for exterema (the most interesting point in a neighborhood)
	// is done by non-maximal suppression

	int BLOCK_W = 16;
	int BLOCK_H = 16;
	cl_event event;
	cl_ulong kernel_begin, kernel_finish;

	clSetKernelArg(non_max_supression, 14, sizeof(cl_mem), (void*)&(d_ipt_count));
	clSetKernelArg(non_max_supression, 15, sizeof(cl_mem), (void*)&d_pixPos);
	clSetKernelArg(non_max_supression, 16, sizeof(cl_mem), (void*)&d_det);
	clSetKernelArg(non_max_supression, 17, sizeof(cl_mem), (void*)&d_laplacian);
	clSetKernelArg(non_max_supression, 18, sizeof(float), (void*)&(thres));

	// Run the kernel for each octave
	for (int o = 0; o < octaves; o++)
	{
		for (int i = 0; i <= 1; i++) {

			cl_mem bResponse = responseMap.at(filter_map[o][i])->getResponses();
			int bWidth = responseMap.at(filter_map[o][i])->getWidth();
			int bHeight = responseMap.at(filter_map[o][i])->getHeight();
			int bFilter = responseMap.at(filter_map[o][i])->getFilter();

			cl_mem mResponse = responseMap.at(filter_map[o][i + 1])->getResponses();
			int mWidth = responseMap.at(filter_map[o][i + 1])->getWidth();
			int mHeight = responseMap.at(filter_map[o][i + 1])->getHeight();
			int mFilter = responseMap.at(filter_map[o][i + 1])->getFilter();
			cl_mem mLaplacian = responseMap.at(filter_map[o][i + 1])->getLaplacian();

			cl_mem tResponse = responseMap.at(filter_map[o][i + 2])->getResponses();
			int tWidth = responseMap.at(filter_map[o][i + 2])->getWidth();
			int tHeight = responseMap.at(filter_map[o][i + 2])->getHeight();
			int tFilter = responseMap.at(filter_map[o][i + 2])->getFilter();
			int tStep = responseMap.at(filter_map[o][i + 2])->getStep();

			size_t localWorkSize[2] = { BLOCK_W, BLOCK_H };
			size_t globalWorkSize[2] = { roundUp(mWidth, BLOCK_W),
				roundUp(mHeight, BLOCK_H) };

			clSetKernelArg(non_max_supression, 0, sizeof(cl_mem), (void*)&tResponse);
			clSetKernelArg(non_max_supression, 1, sizeof(int), (void*)&tWidth);
			clSetKernelArg(non_max_supression, 2, sizeof(int), (void*)&tHeight);
			clSetKernelArg(non_max_supression, 3, sizeof(int), (void*)&tFilter);
			clSetKernelArg(non_max_supression, 4, sizeof(int), (void*)&tStep);
			clSetKernelArg(non_max_supression, 5, sizeof(cl_mem), (void*)&mResponse);
			clSetKernelArg(non_max_supression, 6, sizeof(cl_mem), (void*)&mLaplacian);
			clSetKernelArg(non_max_supression, 7, sizeof(int), (void*)&mWidth);
			clSetKernelArg(non_max_supression, 8, sizeof(int), (void*)&mHeight);
			clSetKernelArg(non_max_supression, 9, sizeof(int), (void*)&mFilter);
			clSetKernelArg(non_max_supression, 10, sizeof(cl_mem), (void*)&bResponse);
			clSetKernelArg(non_max_supression, 11, sizeof(int), (void*)&bWidth);
			clSetKernelArg(non_max_supression, 12, sizeof(int), (void*)&bHeight);
			clSetKernelArg(non_max_supression, 13, sizeof(int), (void*)&bFilter);

			clEnqueueNDRangeKernel(queue, non_max_supression, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, &event);
//			clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &kernel_begin, NULL);
//			clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &kernel_finish, NULL);
			//kernel_total += kernel_finish - kernel_begin;
//			printf("time of kernel2:%d %d\n", kernel_begin, kernel_finish);
		}
	}

}


void compute_with_opencl(std::vector<ResponseLayer *> &responseMap, int *data, int w, int h, float2 * out_pixPos, float *out_det, int *out_laplacian, int *out_ip_count)
{
	clock_t start, finish,t1,t2,t3,t4;
	double duration;
	//clGetPlatformIDs
	cl_uint numPlatforms;
	cl_int err;

	err = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (err != CL_SUCCESS)
	{
		printf("\nGet Platform IDs 1st time fail!\n");
		checkErr(err);
	}
	if (numPlatforms == 0)
	{
		printf("\nNo Platform!\n");
		exit(1);
	}

	printf("\nPlatform Num: %d\n", numPlatforms);

	cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * numPlatforms);

	err = clGetPlatformIDs(numPlatforms, platforms, NULL);
	if (err != CL_SUCCESS)
	{
		printf("\nGet Platform IDs 2ed time fail!\n");
		checkErr(err);
	}

	//clGetPlatformInfo	
	int i = 0;
	char buffer[256];
	for (i = 0; i<numPlatforms; i++)
	{
		printf("For platform %d:\n", i + 1);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(buffer),
			buffer, NULL);
		printf("\tName: %s\n", buffer);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(buffer),
			buffer, NULL);
		printf("\tVendor: %s\n", buffer);
		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION,
			sizeof(buffer), buffer, NULL);
		printf("\tVersion: %s\n", buffer);

		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE,
			sizeof(buffer), buffer, NULL);
		printf("\tProfile: %s\n", buffer);

		err = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS,
			sizeof(buffer), buffer, NULL);
		printf("\tExtensions: %s\n", buffer);
	}

	cl_platform_id platform = platforms[1];

	//clCreateContext
	cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };
#ifdef __INTEL__
	context = clCreateContextFromType(cps, CL_DEVICE_TYPE_CPU, NULL, NULL, &err);
#else
	context = clCreateContextFromType(cps, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);
#endif
	if (err != CL_SUCCESS)
	{
		printf("\nCreate context fail!\n");
		checkErr(err);
	}

	//clGetContextInfo
	cl_uint num_devices;
	cl_device_id device;
	err = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &num_devices, NULL);
	if (err != CL_SUCCESS)
	{
		printf("\nGet Context Info 1st time fail!\n");
		checkErr(err);
	}

	printf("\ndevice num: %d\n", num_devices);

	cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices);

	err = clGetContextInfo(context, CL_CONTEXT_DEVICES, sizeof(cl_device_id) * num_devices, devices, NULL);
	if (err != CL_SUCCESS)
	{
		printf("\nGet Context Info 2ed time fail!\n");
		checkErr(err);
	}

	//clGetDeviceInfo
	for (i = 0; i<num_devices; i++)
	{
		printf("For device %d:\n", i + 1);
		err = clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
		printf("\tName: %s\n", buffer);
		err = clGetDeviceInfo(devices[i], CL_DRIVER_VERSION, sizeof(buffer),
			buffer, NULL);
		printf("\tDriver Version: %s\n", buffer);
		err = clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR, sizeof(buffer),
			buffer, NULL);
		printf("\tVendor: %s\n", buffer);
		err = clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, sizeof(buffer),
			buffer, NULL);
		printf("\tVersion: %s\n", buffer);
	}

	device = devices[0];



	//clCreateCommandQueue
	queue = clCreateCommandQueue(context, device,
		CL_QUEUE_PROFILING_ENABLE, &err);
	if (err != CL_SUCCESS)
	{
		printf("\nCreate command queue fail!\n");
		checkErr(err);
	}



	//读取cl源文件
	char *buf_code;
	size_t length;
	read_source(&buf_code, &length, "HelloWorld_Kernel.cl");



	//创建program对象
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&buf_code, &length, &err);
	if (err != CL_SUCCESS)
	{
		printf("Create Program fail!\n");
		checkErr(err);
	}


	//Build Program
	err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Build Program fail!\n");
		size_t len;
		char buffer[256];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		checkErr(err);
	}

	start = clock();
	cl_event event;

	//clCreateBuffer
	size_t datasize = sizeof(int) * w * h;
	//cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &err);
	cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, datasize, data, &err);
	if (err != CL_SUCCESS)
	{
		printf("Create Buffer A fail!\n");
		checkErr(err);
	}


	//Create Kernel
	cl_kernel kernel = clCreateKernel(program, "computeResponseLayer", &err);
	if (err != CL_SUCCESS)
	{
		printf("Create Kernel fail!\n");
		checkErr(err);
	}
	cl_ulong kernel_total = 0;
	createResponseMap(responseMap, OCTAVES, w, h, SAMPLE_STEP);
	t1=clock();
	computeHessianDet(responseMap, bufferA, w, h, kernel, queue, kernel_total);
	t2=clock();

	datasize = sizeof(int)*w*h;
	cl_mem d_laplacian = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &err);
	datasize = sizeof(float2)*w*h;
	cl_mem d_pixPos = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &err);
	datasize = sizeof(float)*h*w;
	cl_mem d_det = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &err);
	cl_mem d_ipt_count = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &err);

	cl_kernel kernel2 = clCreateKernel(program, "non_max_supression_kernel", &err);
	if (err != CL_SUCCESS)
	{
		printf("Create Kernel fail!\n");
		checkErr(err);
	}
	t3=clock();
	selectIpoints(responseMap, d_laplacian, d_pixPos, d_det, kernel2, queue, d_ipt_count, OCTAVES, THRES, kernel_total);
	t4=clock();
	clEnqueueReadBuffer(queue, d_ipt_count, CL_TRUE, 0, sizeof(int), out_ip_count, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, d_laplacian, CL_TRUE, 0, sizeof(int)*w*h, out_laplacian, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, d_det, CL_TRUE, 0, sizeof(float)*h*w, out_det, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, d_pixPos, CL_TRUE, 0, sizeof(float2) * h*w, out_pixPos, 0, NULL, NULL);

	//finish all command
	//	clFlush(queue);
	//	clFinish(queue);

	//get the kernel execution time and the whole process time
	finish = clock();
	/*	cl_ulong kernel_begin, kernel_finish;
	err = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_QUEUED,
	sizeof(cl_ulong),
	&kernel_begin, NULL);
	if (err != CL_SUCCESS)
	{
	printf("Get Event Profiling Info 1 fail!\n");
	checkErr(err);
	}
	err = clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,
	sizeof(cl_ulong),
	&kernel_finish, NULL);
	if (err != CL_SUCCESS)
	{
	printf("Get Event Profiling Info 2 fail!\n");
	checkErr(err);
	}
	*/
	printf("\nKernel Execution time: %f\n",
		kernel_total / 1000000.0);
	printf("\ntime of first part:%d\ntime of seconde part:%d\n",t2-t1,t4-t3);


	//clean up everything
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(bufferA);
	//	clReleaseCommandQueue(queue);
	//	clReleaseContext(context);



	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\nComputing With Opencl uses %f ms\n", duration * 1000);

}

int main(int argc, char* argv[])
{
	int *data;
	int w = 640;
	int h = 466;
	std::vector<ResponseLayer *> responseMap;
	//读取图像数据
	read_data(argv[1], &data, w, h);
	//为保存处理结果分配内存空间
	//float *out_response = (float *)malloc(sizeof(float)*w*h);
	int * out_laplacian = (int *)malloc(sizeof(int)*w*h);
	float * out_det = (float *)malloc(sizeof(float)*w*h);
	float2 * out_pixPos = (float2 *)malloc(sizeof(float2)*w*h);
	int out_ip_count;
	cl_int err;
	//使用OpenCL接口计算结果
	compute_with_opencl(responseMap, data, w, h, out_pixPos, out_det, out_laplacian, &out_ip_count);

	float * out_response = (float*)malloc(sizeof(float)*w*h);
	cl_mem response = responseMap.at(4)->getResponses();
	int layerWidth = responseMap.at(4)->getWidth();
	int layerHeight = responseMap.at(4)->getHeight();
	size_t datasize = sizeof(float)*layerWidth*layerHeight;
	//clEnqueueReadBuffer, 读取运算结果
	err=clEnqueueReadBuffer(queue, response, CL_TRUE, 0, datasize, out_response, 0, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Enqueu Read Buffer fail!\n");
		checkErr(err);
	}
	write_data_float_2("response_result",out_response,layerHeight,layerWidth);

	write_data("result", out_pixPos, out_det, out_ip_count);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
}


