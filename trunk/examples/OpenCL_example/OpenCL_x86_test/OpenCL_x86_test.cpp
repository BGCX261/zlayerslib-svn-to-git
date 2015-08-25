/*

				zLayersLib
Simple and flexible computing infrastructure for developing
of neuronets, DSP or any other types of data processing projects. 

http://code.google.com/p/zlayerslib/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

This code is distributed under GNU GPL v3 Licence.


========================================================================
    OpenCL_x86_test Project Overview
========================================================================

This application propose binarization with OpenCL kernel
as a simplest demonstration of zLayersLib architecture facilities.

There are 3 Abstract layers:
1)BitmapToVectorLayer convetrs bitmap file to vector.
2)SimpleOpenCLLayer uses data from previous layer and processes it with OpenCL kernel
3)VectorToBitmapLayer saves processed data back to file.
*/

#include "AbstractExecuter.h";
#include "SimpleCLLayer.h";
#include <iostream>;
#include <vector>;
#include "EasyBMP.h";

#include "BitmapToVectorLayer.h";
#include "VectorToBitmapLayer.h"

using namespace std;
int main(void)
{
	cout<<"------------------------------------------"<<endl;
	cout<<"------  zLayersLib OpenCL Example  -------"<<endl;
	cout<<"------------------------------------------"<<endl<<endl<<endl;


	cout<<"Layer1: Bitmap File ------> Bitmap Vector "<<endl;
		BitmapToVectorLayer BL(std::string("lena.bmp"));
		BL.Run(); 
	cout<<"ok"<<endl<<endl;
	
//================================================================================

	cout<<"Layer2: Bitmap Vector --- OpenCL Transform ---> Bitmap Vector"<<endl;
	SimpleCLLayer<unsigned int,unsigned int> CL;
	CL.SetGlobalSize(BL.GetDataSize()); 
	CL.SetInputBuffer(BL.GetOutputBuffer());// Connect CL Input buffer with BL's Output
	CL.NewOutput(BL.GetDataSize()); // 
	CL.SetGlobalRange(BL.GetDataSize()); // Set OpenCL Global worksize
	CL.SetLocalRange(1);				 // Set OpenCL local(grour) worksize
	CL.SetKernelName("simple0");		
	CL.LoadSource("simple0.cl");
	cout<<"Let's execute this code "<<endl;
	cout<<"--------------------------"<<endl;
	cout<<CL.GetSource();
	cout<<"--------------------------"<<endl;
	CL.Run();
	cout<<"ok"<<endl<<endl;

//================================================================================

	cout<<"Layer3: Bitmap Vector ------> Bitmap File"<<endl;
	VectorToBitmapLayer LB(std::string("lena_output.bmp"));
	LB.SetInputBuffer(CL.GetOutputBuffer()); // Connect LB Input buffer with CL's Output
	LB.SetSize(BL.GetWidth(),BL.GetHeight());
	LB.Run();


	cout<<" Done! "<<endl;
	char s[2];
	cin.getline(s,2);
}