#include <iostream>
#include <vector>
#include "convolution.h"
using namespace std;

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
	for (int i = 0; i < N - 1 - (Nh - 1); i++)
	{
		try
		{
			//y_circular[i] = y_linear[i + (Nh - 1)] + y_linear[i + N + (Nh - 1)];
			y_circular.at(i) = y_linear.at(i + (Nh - 1)) + y_linear.at(i + N + (Nh - 1));
		}
		catch (const std::out_of_range& e)
		{
			cout << Nh << endl;
			cout << y_circular.size() << "    " << i << endl;
			cout << y_circular.size() << "    " << i + (Nh - 1) << endl;
			cout << y_linear.size() << "    " << i + N + (Nh - 1) << endl;
			cin >> N;
		}
	}
	y_circular[N - (Nh - 1) - 1] = y_linear[N - 1];
}


template<typename T>
void linker_error_solver_type_circular_convolution(T type)
{
	vector<T> x = { 1, -1, 1, 0 };
	vector<T> h = { 2, 2 };
	vector<T> y_linear = { 0,0,0,0,0,0,0 };
	vector<T> y_circular = { 0,0,0 };
	vector<T> y = { 0,0,2 };
	int N = 0;
	circular_convolution(x, h, y_linear, y_circular, N);
}


void linker_error_solver_circular_convolution()
{
	float x;
	double y;
	int z;
	linker_error_solver_type_circular_convolution(x);
	linker_error_solver_type_circular_convolution(y);
	linker_error_solver_type_circular_convolution(z);
}