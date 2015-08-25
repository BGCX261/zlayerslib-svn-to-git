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
- Class AbstractComputer must be reconstructed(derived from refactored Abstract Executer) ASAP!
*/

#pragma once
#include "abstractlayer.h"

template <class IT, class OT > 
class AbstractComputer :
	public AbstractLayer<IT,OT>
{
public:
	AbstractComputer(void);
	~AbstractComputer(void);

	virtual void PreProcess() { 

	};	// Prepare input data to processing

	virtual void Process() {
		for(size_t i=0;i<ExecuterList.size();i++) ExecuterList[i].Run();
	};		// Process data

		virtual void PostProcess() {
	
	}; // Prepare processed data for output
};

