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

#include "BitmapToVectorLayer.h"


unsigned int BitmapToVectorLayer::GetWidth()
{
		return Bitmap.TellWidth();
}

unsigned int BitmapToVectorLayer::GetHeight()
{
		return Bitmap.TellHeight();
}

unsigned int BitmapToVectorLayer::GetDataSize()
{
		return Bitmap.TellHeight()*Bitmap.TellWidth();
}

BitmapToVectorLayer::BitmapToVectorLayer(void)
{
		filename="";
}

BitmapToVectorLayer::BitmapToVectorLayer(std::string bmpfilename):
	filename(bmpfilename)
{

}

void BitmapToVectorLayer::SetFileName(std::string fn)
{
		filename=fn;
}

BitmapToVectorLayer::~BitmapToVectorLayer(void)
{
}

void BitmapToVectorLayer::PreProcess() {
		Bitmap.ReadFromFile(filename.c_str());
		NewOutput(Bitmap.TellHeight()*Bitmap.TellWidth());
		SetOutputSize(Bitmap.TellHeight()*Bitmap.TellWidth());
	}	// Prepare input data to processing

void BitmapToVectorLayer::Process() {
		// Needed better way to copy PixelData to Vector
		for(unsigned int i=0;i<Bitmap.TellHeight();i++)
		for(unsigned int j=0;j<Bitmap.TellWidth();j++)
		{
			SetOutput(i*Bitmap.TellWidth()+j,Bitmap.GetPixel(i,j).color);
		}
}		// Process data

void BitmapToVectorLayer::PostProcess()
{
} // Prepare processed data for output

