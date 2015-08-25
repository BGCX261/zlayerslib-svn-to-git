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
#include <vector>
#include "abstractexecuter.h"
//#include "abstractneuron.h"

template <class IT, class OT > 
class AbstractLayer :
	public AbstractExecuter<IT,OT>
{
protected:
	std::vector<AbstractExecuter<IT,OT>> ExecuterList; 
public:
	AbstractLayer(void)
	{

	}

	virtual ~AbstractLayer(void)
	{
		ExecuterList.~vector();
	}

	void AddExecuter(AbstractExecuter<IT,OT> E)
	{
		ExecuterList.push_back(E);
	}

	std::vector<AbstractExecuter<IT,OT>>* GetExecuterList()
	{
		return &ExecuterList;
	}

	void Run()
	{
		PreProcess();
		Process();
		PostProcess();
	}

	virtual void PreProcess() { 
		for(size_t i=0;i<ExecuterList.size();i++) ExecuterList[i].PreProcess();
	};	// Prepare input data to processing

	virtual void Process() {
		for(size_t i=0;i<ExecuterList.size();i++) ExecuterList[i].Process();
	};		// Process data

	virtual void PostProcess() {
		for(size_t i=0;i<ExecuterList.size();i++) ExecuterList[i].PostProcess();	
	}; // Prepare processed data for output
};

