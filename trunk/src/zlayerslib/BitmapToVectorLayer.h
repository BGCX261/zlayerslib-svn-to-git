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
#include <iostream>
#include <vector>
#include "abstractlayer.h"
#include "EasyBMP.h"

class BitmapToVectorLayer: public AbstractLayer<std::string,unsigned int>
{
private:
	BMP Bitmap;
	std::string filename;
public:
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetDataSize();
	BitmapToVectorLayer(void);
	BitmapToVectorLayer(std::string bmpfilename);
	void SetFileName(std::string fn);
	~BitmapToVectorLayer(void);

	virtual void PreProcess();
	virtual void Process();
	virtual void PostProcess();
};