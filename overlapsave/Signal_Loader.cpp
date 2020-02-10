#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include "Signal_Loader.h"
#include "chrono"
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

using namespace std;


template<typename T>
Signal_Loader<T>::Signal_Loader(std::vector<T> &x, int Fs) : x(&x), Fs(Fs), end(false)
{
	// empty constructor
}

template<typename T>
void Signal_Loader<T>::operator()()
{
	int nano = 1;
	double Ts = static_cast<double>(nano) / Fs;
	//cout << Ts << "    "<<nano<<"     "<<Fs<<endl;
	//cin >> Ts;
	auto start = std::chrono::steady_clock::now();
	while (!end)
	{
		auto finish = std::chrono::steady_clock::now();
		double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
		if (elapsed_seconds >= Ts)
		{
			cout << elapsed_seconds<<"     "<<Ts << endl;
			T sample = generate_sample();
			//cout << sample << endl;
			x->push_back(sample);
			start = std::chrono::steady_clock::now();
		}
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