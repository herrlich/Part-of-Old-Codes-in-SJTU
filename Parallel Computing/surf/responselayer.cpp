#include "responselayer.h"
unsigned int roundUp(unsigned int value, unsigned int multiple) {

	unsigned int remainder = value % multiple;

	// Make the value a multiple of multiple
	if (remainder != 0) {
		value += (multiple - remainder);
	}

	return value;
}
ResponseLayer::ResponseLayer(int width, int height, int step, int filter)
{	
    this->width = width;
    this->height = height; 
    this->step = step;
    this->filter = filter;
	this->d_laplacian = cl_allocBuffer(sizeof(int)*width*height);//clCreateBuffer(context, CL_MEM_WRITE_ONLY,sizeof(int)*width*height, NULL, &err);
	this->d_responses = cl_allocBuffer(sizeof(float)*width*height);//clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float)*width*height, NULL, NULL);
}

ResponseLayer::~ResponseLayer() 
{
	clReleaseMemObject(this->d_responses);
	clReleaseMemObject(this->d_laplacian);

}

int ResponseLayer::getWidth() 
{

    return this->width;
}

int ResponseLayer::getHeight() 
{

    return this->height;
}

int ResponseLayer::getStep() 
{

    return this->step;
}

int ResponseLayer::getFilter() 
{

    return this->filter;
}

cl_mem ResponseLayer::getLaplacian() 
{

    return this->d_laplacian;
}

cl_mem ResponseLayer::getResponses() 
{

    return this->d_responses;
}