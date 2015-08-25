__kernel void simple0(__global const uchar4 *A, __global uchar4 *C) {
 
    // Get the index of the current element to be processed
    uint i = get_global_id(0);
 
    //uchar4 filteredVal = (uchar4)(0,0,0,0);
    
    // Get monochrome
    uchar M = (uchar)(A[i].z*0.299+A[i].y*0.587+A[i].x*0.114);
    
    // Simplest binarization
    if(M>150)
    {
	C[i]=(uchar4)(255,255,255,255);
    } else {
	C[i]=(uchar4)(0,0,0,0);
    }
    

}
