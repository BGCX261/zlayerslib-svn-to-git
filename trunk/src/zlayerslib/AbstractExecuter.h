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

/*
Todo:
- Write new base non-template class and derive AbstractExecuter from it.
*/

#pragma once
#include <vector>;
#include "AbstractException.h";

template <class IT, class OT > 
class AbstractExecuter
{
protected:
	std::vector<IT> *input;
	std::vector<OT> *output;
	size_t inputsize;
	size_t outputsize;
	bool iowner,oowner;
public:
	AbstractExecuter() { iowner=0;oowner=0;inputsize=0;outputsize=0; }; //default constructor
	AbstractExecuter(size_t osize, size_t isize = 0, std::vector<IT> *inp = NULL);
	~AbstractExecuter(void);

	virtual void PreProcess() { };	// Prepare input data to processing
	virtual void Process() { };		// Process data
	virtual void PostProcess() { }; // Prepare processed data for output

	virtual void SetInputBuffer(std::vector<IT> *inp);
	std::vector<IT>* GetInputBuffer();

	virtual void SetOutputBuffer(std::vector<OT> *outp);
	std::vector<OT>* GetOutputBuffer();

	void SetInputSize(size_t size);
	size_t GetInputSize();

	void SetOutputSize(size_t size);
	size_t GetOutputSize();

	void SetInput(size_t number,IT value);
	IT GetInput(size_t number);

	void SetOutput(size_t number,OT value);
	OT GetOutput(size_t number);

	void NewInput(size_t number);
	void NewOutput(size_t number);

};

template <class IT, class OT >
AbstractExecuter<IT,OT>::AbstractExecuter(size_t osize, size_t isize = 0, std::vector<IT> *inp = NULL)
{
	outputsize=0;
	inputsize =0;

	if(osize<=0)oowner=false;
	else NewOutput(osize);


	iowner=false;
	if(inp!=NULL) 
	{
		input=inp;
		inputsize=input->size();
	}
	else
	{
		if(isize!=0)
		NewInput(isize);
	}
	

}

template <class IT, class OT > AbstractExecuter<IT,OT >::~AbstractExecuter(void)
{
	if(oowner)
	{
		if(!(output==NULL))output->~vector();
	};
	if(iowner)
	{
		if(!(input==NULL))input->~vector();
	};
}

template <class IT, class OT > void AbstractExecuter<IT,OT >::SetInputBuffer(std::vector<IT> *inp)
{
	if(iowner)
	{
		if(!(input==NULL))input->~vector();
		iowner=false;
	};
	if(inp==NULL) throw AbstractExeption("Attempt to set empty input buffer");
	input=inp;
}

template <class IT, class OT > std::vector<IT>* AbstractExecuter<IT,OT >::GetInputBuffer()
{
	return input;
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::SetOutputBuffer(std::vector<OT> *outp)
{
	if(oowner)
	{
		if(!(output==NULL)) output->~vector();
		oowner=false;
	};
	if(outp==NULL) throw AbstractExeption("Attempt to set empty output buffer");
	output=outp;
}

template <class IT, class OT > std::vector<OT>* AbstractExecuter<IT,OT>::GetOutputBuffer()
{
	return output;
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::SetInputSize(size_t size)
{
	if(input==NULL) throw AbstractExeption("Attempt to resize empty input buffer");
	inputsize=size;
	input->resize(size);
}

template <class IT, class OT > size_t AbstractExecuter<IT,OT>::GetInputSize()
{
	return inputsize;
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::SetOutputSize(size_t size)
{
	if(output==NULL) throw AbstractExeption("Attempt to resize empty output buffer");
	outputsize=size;
	output->resize(size);
}

template <class IT, class OT > size_t AbstractExecuter<IT,OT>::GetOutputSize()
{
	return outputsize;
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::SetInput(size_t number,IT value)
{
	if((number<0)||(number>=input->size())) {
		throw AbstractExeption("Out of input buffer boundaries");
	}	else  (*input)[number]=value;		
}

template <class IT, class OT > IT AbstractExecuter<IT,OT>::GetInput(size_t number)
{
	if((number<0)||(number>=input->size())) {
		throw AbstractExeption("Out of input buffer boundaries");
	} 	else return (*input)[number];	
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::SetOutput(size_t number,OT value)
{
	if((number<0)||(number>output->size())) {
		throw AbstractExeption("Out of output buffer boundaries");
	}	else  (*output)[number]=value;		
}

template <class IT, class OT > OT AbstractExecuter<IT,OT>::GetOutput(size_t number)
{
	if((number<0)||(number>output->size())) {
		throw AbstractExeption("Out of output buffer boundaries");
	}	else  return (*output)[number];
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::NewInput(size_t number)
{
		iowner=true;
		input = new std::vector<IT>(number);
		inputsize=number;
}

template <class IT, class OT > void AbstractExecuter<IT,OT>::NewOutput(size_t number)
{
		oowner=true;
		output = new std::vector<OT>(number);
		outputsize=number;
}