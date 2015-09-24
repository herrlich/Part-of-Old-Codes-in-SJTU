#include <stdlib.h>
#include <stdio.h>
#ifndef RESPONSE_LAYER_H
#define RESPONSE_LAYER_H
#include <CL/opencl.h>
void checkErr(cl_int err);
cl_mem cl_allocBuffer(size_t mem_size);
typedef struct {
	float x;
	float y;
}float2;
unsigned int roundUp(unsigned int value, unsigned int multiple);
class ResponseLayer {

  public:
    
    ResponseLayer(int width, int height, int step, int filter);

    ~ResponseLayer();

    int getWidth();

    int getHeight();

    int getStep();
    
    int getFilter();

    cl_mem getResponses(); 

    cl_mem getLaplacian();


  private:
    
    int width;

    int height;  

    int step;

    int filter;

    cl_mem d_responses;

    cl_mem d_laplacian;
};

#endif