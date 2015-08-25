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

#include <sstream>

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}
/*
template <class T>
inline T string_to (std::string s)
{
	std::istringstream ss(s);
	T value;
	ss >> value;
	return value;
}*/

template <typename T>
T string_to(const std::string & s)
{
    std::istringstream stm(s);
    T result;
    stm >> result;
/*
    if(stm.tellg() != s.size())
        throw std::exception("Error in to_string");
		*/
    return result;
}