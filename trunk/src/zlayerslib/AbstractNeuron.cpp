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

#include "AbstractNeuron.h"
#include <iostream>
#include <time.h>;

AbstractNeuron::AbstractNeuron(size_t outputsize): AbstractExecuter(outputsize)
{
		bias = 0;
};

std::vector<double>* AbstractNeuron::GetWeights()
{
		return &weights;
}

void AbstractNeuron::SetWeight(size_t i, double w)
{
		weights[i]=w;
}

double AbstractNeuron::GetWeight(size_t i)
{
		return weights[i];
}

void AbstractNeuron::SetBias(double w)
{
		bias=w;
}

double AbstractNeuron::GetBias()
{
		return bias;
}

void AbstractNeuron::RandomizeWeights()
{
		srand(time(0));
		for(size_t i=0;i<weights.size();i++) 
		weights[i]=(double)(rand())/RAND_MAX;
};

void AbstractNeuron::SetInputBuffer(std::vector<double> *inp)
{
		AbstractExecuter::SetInputBuffer(inp);
		weights.resize((*inp).size());
};

AbstractNeuron::~AbstractNeuron() 
{
		weights.~vector();
		AbstractExecuter::~AbstractExecuter();
};
	
double AbstractNeuron::activate(double inp) //sigmoid by default
{
		return 1/(1-exp(-inp));
}

double AbstractNeuron::GetOutputValue(std::vector<double>* inputs)
{
		if(inputs==NULL) throw AbstractExeption("Attempt to set empty input buffer as neuron input in GetOutputValue");
		double outp=bias;
		for(size_t i=0;i<weights.size();i++) outp+=(*inputs)[i]*weights[i];
		return activate(outp);
}


void AbstractNeuron::Process()
{
		SetOutput(0,GetOutputValue(input));
};		// Process data
