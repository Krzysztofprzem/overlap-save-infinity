#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Signal_Loader.h"

using namespace std;


template <typename T>
void load_samples(std::vector<T> &x_Re, std::string infilename) {
	std::fstream file;
	file.open(infilename, std::ios::in);
	if (!file) {
		std::cerr << "FILE FAILED TO OPEN!" << std::endl;
		exit(-1);
	}
	int n = 0;
	float sample;
	while (file >> sample) {
		x_Re.push_back(sample);
		n++;
		if (n % 1000000 == 0)
			std::cout << "Loaded " << n << " samples" << std::endl;
	}
	std::cout << "Loaded " << n << " samples" << std::endl << std::endl;
	file.close();
}

template <typename T>
void save_samples(std::vector<T> &y, std::string outfilename) {
	std::fstream file;
	file.open(outfilename, std::ios::out, std::ios::app);
	if (!file) {
		std::cerr << "FILE FAILED TO OPEN!" << std::endl;
		exit(-1);
	}
	int n = 1;
	for (; n <= y.size(); n++) {
		file << y[n - 1];
		file << std::endl;
		if (n % 1000000 == 0)
			std::cout << "Saved " << n << " samples" << std::endl;
	}
	std::cout << "Saved " << n - 1 << " samples" << std::endl;
	file.close();
}


template <typename T>
void zero_padding(std::vector<T> &x, int N)
{
	for (int i = 0; i < N; i++)
	{
		x.push_back(0);
	}
}

void create_output_file(string output_path)
{
	fstream output_file;
	output_file.open(output_path, std::ios::out);
	if (!output_file) {
		std::cerr << "FILE FAILED TO OPEN!" << std::endl;
		exit(-1);
	}
	output_file.close();
}


template <typename T>
void init(vector<T> &x, vector<T> &h, vector<T>&y_linear, vector<T>&y_circular, int &Nh, int N, string filter_path, string output_path)
{
	load_samples(h, filter_path);
	Nh = h.size();
	//zero_padding(h, Nh);
	zero_padding(x, Nh-1);
	zero_padding(y_linear, N + Nh - 1);
	zero_padding(y_circular, N - (Nh - 1));
	create_output_file(output_path);
}

template <typename T>
void circular_convolution(vector<T>&x, vector<T>&h, vector<T>&y_linear, vector<T>&y_circular, int N)
{
	int Nx = x.size();
	int Nh = h.size();
	int Ny = y_linear.size();
	// linear convolution
	for (int n = 0; n < Ny; n++)
	{
		T yn = 0;
		for (int k = 0; k < Nh; k++)
		{
			if (((n - k) < 0) || ((n - k) >= N))	yn += 0;
			else									yn += x[n - k] * h[k];
		}
		y_linear[n] = yn;
	}
	// wrapping
	for (int i = 0; i < N-1-(Nh-1); i++)
	{
		y_circular[i] = y_linear[i+ (Nh - 1)] + y_linear[i + N+ (Nh - 1)];
	}
	y_circular[N - (Nh - 1)-1] = y_linear[N - 1];
}




void overlapsave()
{
	string filter_path = "D:\\MOJE\\Projekty\\OpenCL\\OverlapSaveGPU\\OverlapSaveGPU\\Filter.csv";
	string output_path = "output.csv";


	vector<float> h;
	vector<float> x;
	vector<float> y_linear;
	vector<float> y_circular;
	int N = 1024;
	int Nh;
	int Fs = 1000;
	init(x, h, y_linear, y_circular, Nh, N, filter_path, output_path);
	Signal_Loader<float> w(x, Fs);
	boost::thread t(w);
	//circular_convolution(x, h, y_linear, y_circular, N);
	//for (int i = 0; i < y_circular.size(); i++)
	//{
	//	cout << y_circular[i] << endl;
	//}

	int block_number = 0;
	int iteration = 0;
	int block_is_full;

	while (true)
	{
		cout << "";		// (workaround) for some reason without this line, program go to following if despite 
		if(x.size() >= N)
		{
			cout << x.size() << "      " << 1024 << "        " << (x.size() >= 1024) << endl;

			circular_convolution(x, h, y_linear, y_circular, N);
			//save_samples(y_circular, output_path);
			x.erase(x.begin(), x.begin() + N-(Nh-1));
			block_number += 1;
		}
	}
	t.join();
}




int main()
{
	srand(time(NULL));
	overlapsave();
	return 0;
}