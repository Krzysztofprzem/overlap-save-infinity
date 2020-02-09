#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include "Signal_Loader.h"

using namespace std;


template<typename T>
Signal_Loader<T>::Signal_Loader(std::vector<T> &x, int Fs) : x(&x), Fs(Fs)
{
	// empty constructor
}

template<typename T>
void Signal_Loader<T>::operator()()
{
	int nano = 1000000000;
	int Ts = (nano / Fs);
	while (true)
	{
		T sample = generate_sample();
		//cout << sample << endl;
		x->push_back(sample);
		boost::this_thread::sleep_for(boost::chrono::nanoseconds{ Ts });
	}
}

template<typename T>
T Signal_Loader<T>::generate_sample()
{
	T sample = static_cast<double>(rand() % 100000) / 100000;
	return sample;
}


void linker_error_solver()
{
	std::vector<double> x;
	int Fs = 1000;
	Signal_Loader<double>solver(x, Fs);
	solver();
}