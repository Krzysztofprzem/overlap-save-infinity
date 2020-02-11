#include <iostream>
#include <fstream>
#include <vector>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include <string>
#include <boost/thread/thread.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Signal_Loader.h"
#include "chrono"
#include "filesIO.h"

using namespace std;

template<typename T>
Signal_Loader<T>::Signal_Loader(std::vector<T> &x, int Fs) : x(&x), Fs(Fs), end(false)
{
	string path = "D:\\MOJE\\Projekty\\OpenCL\\OverlapSaveGPU\\OverlapSaveGPU\\Samples.csv";
	load_samples(x_default, path);
	// empty constructor
}


template<typename T>
void Signal_Loader<T>::operator()()
{
	double Ts = static_cast<double>(1) / Fs;
	auto start = std::chrono::steady_clock::now();
	auto finish = std::chrono::steady_clock::now();
	while (!end)
	{
		finish = std::chrono::steady_clock::now();
		double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
		if (elapsed_seconds >= Ts)
		{
			//cout << elapsed_seconds<<"     "<<Ts << endl;
			T sample = generate_sample();
			//cout << sample << endl;
			x->push_back(sample);
			//cout << x->size()<<endl;
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
void linker_error_solver_type_Signal_Loader(std::vector<T> x, int Fs = 1000)
{
	Signal_Loader<T>solver(x, Fs);
	solver();
}


void linker_error_solver_Signal_Loader()
{
	std::vector<float> x;
	std::vector<double> y;
	std::vector<int> z;
	linker_error_solver_type_Signal_Loader(x);
	linker_error_solver_type_Signal_Loader(y);
	linker_error_solver_type_Signal_Loader(z);
}