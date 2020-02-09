#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include "Signal_Loader.h"

using namespace std;


template<typename T>
Signal_Loader<T>::Signal_Loader(std::vector<T> &x, int Fs) : x(&x), Fs(Fs), end(false)
{
	// empty constructor
}

template<typename T>
void Signal_Loader<T>::operator()()
{
	int nano = 1000000000;
	int Ts = (nano / Fs);
	while (!end)
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


template<typename T>
void linker_error_solver_type(std::vector<T> x, int Fs = 1000)
{
	Signal_Loader<T>solver(x, Fs);
	solver();
}

void linker_error_solver()
{
	std::vector<float> x;
	std::vector<double> y;
	std::vector<int> z;
	linker_error_solver_type(x);
	linker_error_solver_type(y);
	linker_error_solver_type(z);
}