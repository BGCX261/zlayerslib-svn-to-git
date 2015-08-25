/*
				zLayersLib
Simple and flexible computing infrastructure for developing
of neuronets, DSP or any other types of data processing projects. 

http://code.google.com/p/zlayerslib/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

This code is distributed under GNU GPL v3 Licence.
*/

#include "VectorToBitmapLayer.h"

void VectorToBitmapLayer::SetSize(unsigned int w,unsigned int h)
{
		Width=w;
		Height=h;
}

VectorToBitmapLayer::VectorToBitmapLayer(std::string bmpfilename)
{
		NewOutput(1);
		if(!bmpfilename.empty()) SetOutput(0,bmpfilename);
}

VectorToBitmapLayer::~VectorToBitmapLayer(void)
{

}

void VectorToBitmapLayer::PreProcess()
{

		Bitmap.SetSize(Width,Height);
};	// Prepare input data to processing

void VectorToBitmapLayer::Process() {
		// Needed better way to copy PixelData to Vector
		for(unsigned int i=0;i<Height;i++)
		for(unsigned int j=0;j<Width;j++)
		{
			Bitmap.SetPixel(i,j,GetInput(j+i*Width));
			//SetOutput(i*Bitmap.TellWidth()+j,Bitmap.GetPixel(i,j).color);
		}
		Bitmap.WriteToFile(GetOutput(0).c_str());
};		// Process data

void VectorToBitmapLayer::PostProcess() {
}; // Prepare processed data for output
