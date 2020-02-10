#pragma once
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>

template<typename T>
class Signal_Loader
{
public:
	Signal_Loader(std::vector<T> &x, int Fs);
	void operator()();
public:
	std::vector<T> *x;
	int Fs;
	bool end;
	T generate_sample();
};