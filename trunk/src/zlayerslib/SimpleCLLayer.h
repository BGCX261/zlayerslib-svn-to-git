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
#include <iostream>
#include <utility>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <fstream>
#include "generic_utils.h"

//#define TIXML_USE_STL
//#include "tinyxml\tinyxml.h"


template <class IT, class OT > 
class SimpleCLLayer :
	public AbstractLayer<IT,OT>
{
protected:
	std::string Buildinfo;
	bool doubleprec_avalible;
	std::string xmlfilename;
	unsigned int PlatformNumber;
	unsigned int DeviceNumber;
	unsigned int DeviceType;
	unsigned int SetDeviceType(std::string s);
	std::string sourcefile;
	std::string sourceCode;
	std::string KernelName;

	std::vector<cl::Platform> platforms;
	cl::Context				  context;
	std::vector<cl::Device>   devices;
	cl::CommandQueue		  queue;
	cl::Program::Sources	  src;
	cl::Program				  program;
	cl::Kernel				  kernel;
    cl::NDRange				  global;
    cl::NDRange				  local;
	cl::Buffer				  bufferIn;
	cl::Buffer				  bufferOut;

	unsigned int globalsize;

public:
	SimpleCLLayer(unsigned int globalsz=0,std::string xmlfile="");
	~SimpleCLLayer(void);
	void LoadProperties(std::string xmlfile);
	void LoadSource(std::string filename="");
	std::string GetSource();
	void Compile();
	void MakeContext();
	void SetKernelName(std::string kname);
	void SetGlobalRange(unsigned int x,unsigned int y=0,unsigned int z=0);
	void SetLocalRange(unsigned int x,unsigned int y=0,unsigned int z=0);
	void SetGlobalSize(unsigned int sz);


	virtual void PreProcess();	// Prepare input data to processing
	virtual void Process();		// Process data
	virtual void PostProcess(); // Prepare processed data for output

};

template <class IT, class OT > void SimpleCLLayer<IT,OT>::SetGlobalSize(unsigned int sz)
{
	globalsize=sz;
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::SetKernelName(std::string kname)
{
	KernelName = kname;
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::SetGlobalRange(unsigned int x,unsigned int y=0,unsigned int z=0)
{
	if(y==0) global = cl::NDRange(x);
	else
	if(z==0) global = cl::NDRange(x,y);
	else
	global = cl::NDRange(x,y,z);
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::SetLocalRange(unsigned int x,unsigned int y=0,unsigned int z=0)
{
	if(y==0) local = cl::NDRange(x);
	else
	if(z==0) local = cl::NDRange(x,y);
	else
	local = cl::NDRange(x,y,z);
}
template <class IT, class OT > void SimpleCLLayer<IT,OT>::MakeContext()
{
	try
	{
		// Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = { 
            CL_CONTEXT_PLATFORM, 
            (cl_context_properties)(platforms[PlatformNumber])(), 
            0 
        };
        context = cl::Context(DeviceType, cps);
        devices = context.getInfo<CL_CONTEXT_DEVICES>();
 
        // Create a command queue and use the first device
        cl::CommandQueue queue0 = cl::CommandQueue(context, devices[DeviceNumber]);
		queue = queue0;

	} catch(cl::Error &error) {
		std::string s(to_string(error.what())+"SimpleCLLayer exception:"+to_string(error.err()));
		throw AbstractExeption(s.c_str());
    }
}


template <class IT, class OT > void SimpleCLLayer<IT,OT>::Compile()
{
	try
	{
        // Create Program source
        cl::Program::Sources source0(1, std::make_pair(sourceCode.c_str(), sourceCode.length()+1));
 
        // Make program of the source code in the context
        cl::Program program0 = cl::Program(context, source0);
 
        // Build program for these specific devices
        program0.build(devices);
		cl::Kernel kernel0(program0, KernelName.c_str());
		kernel = kernel0;

	} catch(cl::Error &error) {
		std::string s(to_string(error.what())+"SimpleCLLayer exception:"+to_string(error.err()));
		throw AbstractExeption(s.c_str());
    }
}

template <class IT, class OT > SimpleCLLayer<IT,OT>::~SimpleCLLayer(void)
{

}

template <class IT, class OT > std::string SimpleCLLayer<IT,OT>::GetSource()
{
	return sourceCode;
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::LoadSource(std::string filename="")
{
	 // Read source from file
	if(!filename.empty()) sourcefile=filename;
     std::ifstream sourceFile(sourcefile);
     sourceCode = std::string(std::istreambuf_iterator<char>(sourceFile),(std::istreambuf_iterator<char>()));
}

template <class IT, class OT > unsigned int SimpleCLLayer<IT,OT>::SetDeviceType(std::string s)
{

	if (s=="cpu")			DeviceType=CL_DEVICE_TYPE_CPU;
	else
	if(s=="gpu")			DeviceType=CL_DEVICE_TYPE_GPU;
	else
	if(s=="accelerator")	DeviceType=CL_DEVICE_TYPE_ACCELERATOR;
	else
	if(s=="all")			DeviceType=CL_DEVICE_TYPE_ALL ;
	else					DeviceType=CL_DEVICE_TYPE_DEFAULT;
	return DeviceType;
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::LoadProperties(std::string xmlfile)
{
	//Must be XML-parser in here!
}


template <class IT, class OT > SimpleCLLayer<IT,OT>::SimpleCLLayer(unsigned int globalsz=0,std::string xmlfile=""):
xmlfilename(xmlfile),globalsize(globalsz)
{
	PlatformNumber=0;
	DeviceNumber=0;
	DeviceType=CL_DEVICE_TYPE_GPU;
	KernelName="simple0";
	sourcefile = "simple0.cl";

	if(xmlfile!="")
	{
				LoadProperties(xmlfilename);
	}

	if(globalsize!=0)
	{
		NewInput(globalsize);
		NewOutput(globalsize);
	}
		// Get available platforms
        cl::Platform::get(&platforms);
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::PreProcess()
{
	MakeContext();
	Compile();
	try
	{
		// Create memory buffers
        bufferIn = cl::Buffer(context, CL_MEM_READ_ONLY, globalsize * sizeof(IT));
        bufferOut = cl::Buffer(context, CL_MEM_WRITE_ONLY, globalsize * sizeof(OT));
 
        // Copy lists A and B to the memory buffers
        queue.enqueueWriteBuffer(bufferIn, CL_TRUE, 0, globalsize * sizeof(IT), input->data());

        // Set arguments to kernel
        kernel.setArg(0, bufferIn);
        kernel.setArg(1, bufferOut);

	} catch(cl::Error &error) {
		std::string s(to_string(error.what())+" SimpleCLLayer exception:"+to_string(error.err()));
		throw AbstractExeption(s.c_str());
    }
}

template <class IT, class OT >void 	SimpleCLLayer<IT,OT>::Process()
{
	try 
	{
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

	} catch(cl::Error &error) {
		std::string s(to_string(error.what())+" SimpleCLLayer exception:"+to_string(error.err()));
		throw AbstractExeption(s.c_str());
    }
}

template <class IT, class OT > void SimpleCLLayer<IT,OT>::PostProcess()
{

   try { 
        queue.enqueueReadBuffer(bufferOut, CL_TRUE, 0, globalsize * sizeof(OT), output->data());
    } catch(cl::Error error) {
				std::cout << error.what() << "(" << error.err() << ")" << std::endl;
    }
 
}

