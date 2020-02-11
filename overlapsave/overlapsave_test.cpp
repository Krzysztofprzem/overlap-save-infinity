#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>
#include "convolution.h"

using namespace std;

BOOST_AUTO_TEST_CASE(myTestCase)
{
  BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}


BOOST_AUTO_TEST_CASE(cyclicConvolutionTest)
{
	vector<float> x = { 1, -1, 1, 0 };
	vector<float> h = {2, 2};
	vector<float> y_linear = { 0,0,0,0,0,0,0 };
	vector<float> y_circular = { 0,0,0 };
	vector<float> y = { 0,0,2 };

	int N = 4;
	circular_convolution(x, h, y_linear, y_circular, N);

	//for (int i = 0; i < y_circular.size(); i++)
	//	cout << y_circular[i] << endl;


	BOOST_TEST((y_circular == y));
}