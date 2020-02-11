#pragma once
#include <vector>
using namespace std;


template <typename T>
void load_samples(std::vector<T> &x_Re, std::string infilename);

template <typename T>
void save_samples(std::vector<T> &y, std::string outfilename);