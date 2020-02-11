#include <iostream>
#include <fstream>
#include "filesIO.h"

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



template<typename T>
void linker_error_solver_type_filesIO(std::vector<T> x)
{
	load_samples(x, "/file.csv");
	save_samples(x, "/file.csv");
}


void linker_error_solver_filesIO()
{
	std::vector<float> x;
	std::vector<double> y;
	std::vector<int> z;
	linker_error_solver_type_filesIO(x);
	linker_error_solver_type_filesIO(y);
	linker_error_solver_type_filesIO(z);
}