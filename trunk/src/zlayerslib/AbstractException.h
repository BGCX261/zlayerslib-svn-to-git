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
#include <iostream>;

class AbstractExeption
{
public:
	std::string Message;
	AbstractExeption(const char* m)
	{
		Message=m;
		std::cout<<"Abstract Exception:"<<m<<std::endl;
	}

	~AbstractExeption()
	{
		Message="";
	}
};