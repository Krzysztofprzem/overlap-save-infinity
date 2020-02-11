#pragma once
#include <vector>
using namespace std;

template <typename T>
void circular_convolution(vector<T>&x, vector<T>&h, vector<T>&y_linear, vector<T>&y_circular, int N);
