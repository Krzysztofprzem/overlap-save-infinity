#include <gtest/gtest.h>
#include <vector>
#include "unit_tests.h"
#include <boost/test/unit_test.hpp>
#include "host.h"


BOOST_AUTO_TEST_CASE(circular_convolution_test)
{
	vector<float> h = {2, 2};
	vector<float> x = {1, -1, 1, 0};
	vector<float> y_linear;
	vector<float> y_circular;
	int N = x.size();
	int Nh = h.size();
	y_linear.resize(N * 2);
	y_circular.resize(N);

	vector<float> y = {2, 0, 0, 2};

	circular_convolution(x, h, y_linear, y_circular, N);

	BOOST_CHECK(y_circular == y);
}



int run_tests(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}