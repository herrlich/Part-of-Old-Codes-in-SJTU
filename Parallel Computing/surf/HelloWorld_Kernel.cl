#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable  
#pragma OPENCL EXTENSION cl_amd_printf:enable

inline int mina(int a,int b){
	return a>b?b:a;
}

inline float maxa(float a,float b){
	return a>b?a:b;
}

float BoxIntegral(__global int *data,int width,int height,int row,int col,int rows,int cols){
	
	int r1=mina(row,height)-1;
	int c1=mina(col,width)-1;
	int r2=mina(row+rows,height)-1;
	int c2=mina(col+cols,width)-1;
	
    float A=0.0f, B=0.0f, C=0.0f, D=0.0f;
    if (r1 >= 0 && c1 >= 0) A = data[r1 * width + c1];
    if (r1 >= 0 && c2 >= 0) B = data[r1 * width + c2];
    if (r2 >= 0 && c1 >= 0) C = data[r2 * width + c1];
    if (r2 >= 0 && c2 >= 0) D = data[r2 * width + c2];

    return maxa(0.f, A - B - C + D);
}

__kernel void computeResponseLayer(__global int *data,int i_width,int i_height,__global float *responses,__global int *laplacian,int width,int height,int step,int filter){	
	int b=(filter-1)/2;
	int l=filter/3;
	int w=filter;
	
    float inverse_area = 1.f/(w*w);           // normalisation factor
    float Dxx=0.f, Dyy=0.f, Dxy=0.f;
	
	int ar=get_global_id(1);
	int ac=get_global_id(0);
	int index=ar*width+ac;
	

    // get the image coordinates
    int r = ar * step;
    int c = ac * step;
	if(r >= i_height || c >= i_width) {
        return;
    }
	int r1,r2,c1,c2;
	float A,B,C,D,E;
	r1=mina(r-l,i_height)-1;
	r2=mina(r+l,i_height)-1;
	c1=mina(c-b,i_width)-1;
	c2=mina(c-b+w,i_width)-1;
	A=B=C=D=0;
	if (r1>=0 && c1>=0)A=data[r1*i_width+c1];
	if (r1>=0 && c2>=0)B=data[r1*i_width+c2];
	if (r2>=0 && c1>=0)C=data[r2*i_width+c1];
	if (r2>=0 && c2>=0)D=data[r2*i_width+c2];
	Dxx+=maxa(0.f,A-B-C+D);
	c1=mina(c-l/2,i_width)-1;
	c2=mina(c-l/2+l,i_width)-1;
	A=B=C=D=0;
	if (r1>=0 && c1>=0)A=data[r1*i_width+c1];
	if (r1>=0 && c2>=0)B=data[r1*i_width+c2];
	if (r2>=0 && c1>=0)C=data[r2*i_width+c1];
	if (r2>=0 && c2>=0)D=data[r2*i_width+c2];
	Dxx-=maxa(0.f,A-B-C+D)*3;

	c1=mina(c-l,i_width)-1;
	c2=mina(c+l,i_width)-1;
	A=B=C=D=E=0;
	if (r1>=0 && c1>=0)A=data[r1*i_width+c1];
	if ((r1+r2)/2>=0 && c1>=0)B=data[(r1+r2)/2*i_width+c1];
	if (r1>=0 && (c1+c2)/2>=0)C=data[r1*i_width+(c2+c1)/2];
	if ((r1+r2)>=0 && (c1+c2)/2>=0)D=data[(r1+r2)/2*i_width+(c1+c2)/2];
	Dxy-=maxa(0.f,D-B-C+A);
	A=0.f;
	if (r1>=0 && c2>=0)E=data[r1*i_width+c2];
	if ((r1+r2)/2>=0 && c2>=0)A=data[(r1+r2)/2*i_width+c2];
	Dxy+=maxa(0.f,A+C-E-D);
	C=E=0.f;
	if (r2>=0 && c2>=0)E=data[r2*i_width+c2];
	if (r2>=0 && (c1+c2)/2>=0)C=data[r2*i_width+(c2+c1)/2];
	Dxy-=maxa(0.f,E-A-C+D);
	A=0.f;
	if (r2>=0 && c1>=0)A=data[r1*i_width+c2];
	Dxy+=maxa(0.f,C-D-A+B);

	r1=mina(r-b,i_height)-1;
	r2=mina(r-b+w,i_height)-1;
	A=B=C=D=0.f;
	if (r1>=0 && c1>=0)A=data[r1*i_width+c1];
	if (r1>=0 && c2>=0)B=data[r1*i_width+c2];
	if (r2>=0 && c1>=0)C=data[r2*i_width+c1];
	if (r2>=0 && c2>=0)D=data[r2*i_width+c2];
	Dyy+=maxa(0.f,A-B-C+D);
	r1=mina(r-l/2,i_height)-1;
	r2=mina(r-l/2+l,i_height)-1;
	A=B=C=D=0;
	if (r1>=0 && c1>=0)A=data[r1*i_width+c1];
	if (r1>=0 && c2>=0)B=data[r1*i_width+c2];
	if (r2>=0 && c1>=0)C=data[r2*i_width+c1];
	if (r2>=0 && c2>=0)D=data[r2*i_width+c2];
	Dyy-=maxa(0.f,A-B-C+D)*3;
		  
        // Normalise the filter responses with respect to their size
    Dxx *= inverse_area;
    Dyy *= inverse_area;
    Dxy *= inverse_area;
        // Get the determinant of hessian response & laplacian sign
    responses[index] =(Dxx * Dyy - 0.81f * Dxy * Dxy);
    laplacian[index] =(((Dxx + Dyy)>= 0) ? 1 : 0);
}


inline int getLaplacian(__global float* layer, int c, int r, int width)
{
    return layer[r*width+c];  
}


inline float getResponse(__global float* layer, int c, int r, int width, int scale)
{ 
    return layer[r*scale*width+c*scale];
}

bool interpolateExtremum(      int  r, 
                               int  c, 					
                   __global    int* ipt_count,  
                            float2* pos,
                             float* det_scale,
                               int* laplacian,
                       __global float*  t,
                               int  tWidth,
                               int  tHeight,
                               int  tStep,
                       __global float*  m,
                       __global int*  mLaplacian,
                               int  mWidth,
                               int  mHeight,
                               int  mFilter,  
                       __global float*  b,
                               int  bWidth,
                               int  bHeight,
                               int  bFilter)
{

    // ---------------------------------------
    // Step 1: Calculate the 3D derivative
    // ---------------------------------------
    int mScale = mWidth/tWidth;

    int bScale = bWidth/tWidth;
    
    float dx, dy, ds; 

    dx = (getResponse(m, c+1, r,   mWidth, mScale) - getResponse(m, c-1, r,   mWidth, mScale)) / 2.0f;
    dy = (getResponse(m, c,   r+1, mWidth, mScale) - getResponse(m, c,   r-1, mWidth, mScale)) / 2.0f;
    ds = (getResponse(t, c,   r,   tWidth, 1)      - getResponse(b, c,   r,   bWidth, bScale)) / 2.0f;
    
    // ---------------------------------------
    // Step 2: Calculate the inverse Hessian
    // ---------------------------------------
    
    float v;
    
    float dxx, dyy, dss, dxy, dxs, dys;

    v = getResponse(m, c, r, mWidth, mScale);

    dxx =  getResponse(m, c+1, r,   mWidth, mScale) + getResponse(m, c-1, r,   mWidth, mScale) - 2.0f*v;
    dyy =  getResponse(m, c,   r+1, mWidth, mScale) + getResponse(m, c,   r-1, mWidth, mScale) - 2.0f*v;
    dss =  getResponse(t, c,   r,   tWidth, 1)      + getResponse(b, c,   r,   bWidth, bScale) - 2.0f*v;
    dxy = (getResponse(m, c+1, r+1, mWidth, mScale) - getResponse(m, c-1, r+1, mWidth, mScale) -
           getResponse(m, c+1, r-1, mWidth, mScale) + getResponse(m, c-1, r-1, mWidth, mScale))/4.0f;
    dxs = (getResponse(t, c+1, r,   tWidth, 1)      - getResponse(t, c-1, r,   tWidth, 1) -
           getResponse(b, c+1, r,   bWidth, bScale) + getResponse(b, c-1, r,   bWidth, bScale))/4.0f;
    dys = (getResponse(t, c,   r+1, tWidth, 1)      - getResponse(t, c,   r-1, tWidth, 1) -
           getResponse(b, c,   r+1, bWidth, bScale) + getResponse(b, c,   r-1, bWidth, bScale))/4.0f;

    float H0 = dxx;
    float H1 = dxy;
    float H2 = dxs;
    float H3 = dxy;
    float H4 = dyy;
    float H5 = dys;
    float H6 = dxs;
    float H7 = dys;
    float H8 = dss;

    // NOTE Although the inputs are the same, the value of determinant (and
    //      therefore invdet) vary from the CPU version
    
    float determinant = H0*(H4*H8-H7*H5)-H1*(H3*H8-H5*H6)+H2*(H3*H7-H4*H6);
         
    float invdet = 1.0f / determinant;
       
    float invH0 =  (H4*H8-H7*H5)*invdet;
    float invH1 = -(H3*H8-H5*H6)*invdet;
    float invH2 =  (H3*H7-H6*H4)*invdet;
    float invH3 = -(H1*H8-H2*H7)*invdet;
    float invH4 =  (H0*H8-H2*H6)*invdet;
    float invH5 = -(H0*H7-H6*H1)*invdet;
    float invH6 =  (H1*H5-H2*H4)*invdet;
    float invH7 = -(H0*H5-H3*H2)*invdet;
    float invH8 =  (H0*H4-H3*H1)*invdet;
    
    // ---------------------------------------
    // Step 3: Multiply derivative and Hessian
    // ---------------------------------------
    
    float xi = 0.0f, xr = 0.0f, xc = 0.0f;
    
    xc =  invH0 * dx * -1.0f;
    xc += invH1 * dy * -1.0f;
    xc += invH2 * ds * -1.0f;
    
    xr =  invH3 * dx * -1.0f;
    xr += invH4 * dy * -1.0f;
    xr += invH5 * ds * -1.0f;
    
    xi =  invH6 * dx * -1.0f;
    xi += invH7 * dy * -1.0f;
    xi += invH8 * ds * -1.0f;

    // Check if point is sufficiently close to the actual extremum
    if(fabs(xi) < 0.5f && fabs(xr) < 0.5f && fabs(xc) < 0.5f)
    {
        int filterStep = mFilter - bFilter;
        
        // Store values related to interest point
        (*pos).x =(float)((c + xc)*tStep);    
        (*pos).y =(float)((r + xr)*tStep);    
        //*det_scale = (float)(0.1333f)*(mFilter + (xi*filterStep));   
        *det_scale = getResponse(m, c,   r, mWidth, mScale);
        int scale = mWidth/tWidth;  
        *laplacian = getLaplacian(mLaplacian, c*scale, r*scale, mWidth); 
       
        return true;
    }
    return false;
}


//! Check whether point really is a maximum
bool isExtremum( __global float*  t,int  tWidth,int  tHeight,int  tFilter,int  tStep,
                 __global float*  m,int  mWidth,int  mHeight,  
                 __global float*  b,int  bWidth,int  bHeight,                
                  int  c, int  r,float  threshold)
{
    int layerBorder = (tFilter+1)/(2*tStep);

    // If any accesses would read out-of-bounds, this point is not a maximum
    if(r <= layerBorder || r >= tHeight - layerBorder ||
       c <= layerBorder || c >= tWidth - layerBorder) {
       
       return false;
    }
   
    int mScale = mWidth/tWidth;
    
    // Candidate for local maximum
    float candidate = getResponse(m, c, r, mWidth, mScale);
    
    if(candidate < threshold) {
        return false;
    }
    
    // If any response in 3x3x3 is greater candidate not maximum
    float localMax =          getResponse(t, c-1, r-1, tWidth, 1);
    localMax = maxa(localMax, getResponse(t, c,   r-1, tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c+1, r-1, tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c-1, r,   tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c,   r,   tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c+1, r,   tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c-1, r+1, tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c,   r+1, tWidth, 1));
    localMax = maxa(localMax, getResponse(t, c+1, r+1, tWidth, 1));
    
    int bScale = bWidth/tWidth;

    localMax = maxa(localMax, getResponse(b, c-1, r-1, bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c,   r-1, bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c+1, r-1, bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c-1, r,   bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c,   r,   bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c+1, r,   bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c-1, r+1, bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c,   r+1, bWidth, bScale));
    localMax = maxa(localMax, getResponse(b, c+1, r+1, bWidth, bScale));
    
    //int mScale = mWidth/tWidth;

    localMax = maxa(localMax, getResponse(m, c-1, r-1, mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c,   r-1, mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c+1, r-1, mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c-1, r,   mWidth, mScale));
    // This is the candidate pixel
    localMax = maxa(localMax, getResponse(m, c+1, r,   mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c-1, r+1, mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c,   r+1, mWidth, mScale));
    localMax = maxa(localMax, getResponse(m, c+1, r+1, mWidth, mScale));
    
    // If localMax > candidate, candidate is not the local maxima
    if(localMax > candidate) {
       return false;
    }
    
    return true;   
}


__kernel
void non_max_supression_kernel(__global float*  tResponse,int  tWidth,int  tHeight,int  tFilter,int  tStep,
								__global float*  mResponse,__global int*  mLaplacian,int  mWidth,int  mHeight,  int  mFilter,
								__global float*  bResponse,int  bWidth,int  bHeight,int  bFilter,  
								 __global    int* ipt_count,__global float2* d_pixPos,__global  float* d_det,
								__global    int* d_laplacian,float  threshold)
{  
    int r = get_global_id(1);
    int c = get_global_id(0);            
    
    float2 pixpos;
    float scale;
    int laplacian;
    // Check the block extremum is an extremum across boundaries.          
    if(isExtremum(tResponse, tWidth, tHeight, tFilter, tStep, mResponse,
                  mWidth, mHeight, bResponse, bWidth, bHeight, c, r, threshold))
    {  
//        if(interpolateExtremum(r, c, ipt_count, &pixpos, &scale, 
//            &laplacian, tResponse, tWidth, tHeight, tStep, mResponse, 
//            mLaplacian, mWidth, mHeight, mFilter, bResponse, bWidth, bHeight, 
//            bFilter)) {      			 			
			
            int index = atom_add(&ipt_count[0], 1);
			pixpos.x=r;//*mWidth/tWidth;
			pixpos.y=c;//*mWidth/tWidth;
            d_pixPos[index] = pixpos;
            d_det[index] = getResponse(mResponse,c,r,mWidth,mWidth/tWidth);
//        }
    }
}
