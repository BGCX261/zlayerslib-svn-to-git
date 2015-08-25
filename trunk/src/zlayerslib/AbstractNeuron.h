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
#include "abstractexecuter.h";

class AbstractNeuron:
	public AbstractExecuter<double,double>
{
private:
	std::vector<double> weights;
	double bias;
public:

	std::vector<double>* GetWeights();
	void SetWeight(size_t i, double w);
	double GetWeight(size_t i);

	void SetBias(double w);
	double GetBias();

	virtual void RandomizeWeights();
	virtual void SetInputBuffer(std::vector<double> *inp);

	AbstractNeuron(size_t outputsize = 1);
	~AbstractNeuron();

	virtual double activate(double inp); //sigmoid by default
	virtual double GetOutputValue(std::vector<double>* inputs);
	virtual void PreProcess() {};	// Prepare input data to processing
	virtual void Process();
	virtual void PostProcess() {}; // Prepare processed data for output
};

