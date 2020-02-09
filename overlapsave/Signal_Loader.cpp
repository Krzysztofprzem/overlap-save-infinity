/*
template<typename T>
class Signal_Loader
{
public:
	Signal_Loader(std::vector<T> &x, int Fs) : x(x), Fs(Fs)
	{
		// empty constructor
	}

	void operator()()
	{
		int nano = 1000000000;
		int Ts = (nano / Fs);
		while (true)
		{
			boost::this_thread::sleep_for(boost::chrono::nanoseconds{ Ts });
			cout << "aa" << endl;
		}
	}

private:
	std::vector<T> x;
	int Fs;
};
*/