#pragma once
#include <vector>
#include <string>

using namespace std;


template <typename T>
void load_samples(std::vector<T> &x_Re, std::string infilename);

template <typename T>
void save_samples(std::vector<T> &y, std::string outfilename);

template <typename T>
void zero_padding(std::vector<T> &x, int N);

void create_output_file(string output_path);

template <typename T>
void init(vector<T> &x, vector<T> &h, vector<T>&y_linear, vector<T>&y_circular, int &Nh, int N, string filter_path, string output_path);

template <typename T>
void circular_convolution(vector<T>&x, vector<T>&h, vector<T>&y_linear, vector<T>&y_circular, int N);

void overlapsave();