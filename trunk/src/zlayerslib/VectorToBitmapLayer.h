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

#pragma once
#include "abstractlayer.h"
#include "EasyBMP.h"

class VectorToBitmapLayer:
	public AbstractLayer<unsigned int,std::string>
{
private:
	BMP Bitmap;
	unsigned int Width;
	unsigned int Height;

public:
	void SetSize(unsigned int w,unsigned int h);
	VectorToBitmapLayer(std::string bmpfilename="");
	~VectorToBitmapLayer(void);

	virtual void PreProcess();
	virtual void Process();
	virtual void PostProcess();
};

