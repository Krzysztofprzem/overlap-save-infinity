#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "host.h"
#include "Signal_Loader.h"
#include "filesIO.h"
#include "convolution.h"

#include <SFML/Audio.hpp>

using namespace std;

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
	zero_padding(y_linear, 2 * N - 1);
	zero_padding(y_circular, N - (Nh - 1));
	create_output_file(output_path);
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
	int Fs = 20000;
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


void microphone_input()
{
	// get the available sound input device names
	std::vector<std::string> availableDevices = sf::SoundRecorder::getAvailableDevices();

	for (int i = 0; i < availableDevices.size(); i++)
	{
		cout << i << "    " << availableDevices[i] << endl;
	}


	// choose a device
	std::string inputDevice = availableDevices[0];

	// create the recorder
	sf::SoundBufferRecorder recorder;

	// set the device
	if (!recorder.setDevice(inputDevice))
	{
		exit(0);
	}

	//MyRecorder *rec = new SoundBufferRecorder();

	cout << "start" << endl;
	// start the capture
	while(true)
	{
		auto start = std::chrono::steady_clock::now();
		auto finish = std::chrono::steady_clock::now();
		start = std::chrono::steady_clock::now();
		recorder.start(1000);
		while (true)
		{
			finish = std::chrono::steady_clock::now();
			double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();
			if (elapsed_seconds >= 1)
			{
				recorder.stop();
				cout << elapsed_seconds << " seconds" << endl;
				const sf::SoundBuffer& buffer = recorder.getBuffer();
				std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
				const sf::Int16* samples = buffer.getSamples();
				std::size_t count = buffer.getSampleCount();
				cout << count << "    " << samples[count - 1] << endl;
				break;
			}
			//else
			//cout << elapsed_seconds << endl;
		}
	}
	//stop the capture
	cout << "end" << endl;

	// retrieve the buffer that contains the captured audio data
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
	const sf::Int16* samples = buffer.getSamples();
	std::size_t count = buffer.getSampleCount();
	cout << count << "    " << samples[count - 1] << endl;
	//for (int i = 0; i < count; i++)
	//{
	//	//recorder.start(100);
	//	//Sleep(5000);
	//	//recorder.stop();

	//	//std::size_t count = buffer.getSampleCount();

	//	if(count>0)
	//		cout << i << "    " << count << "    " <<samples[count-1] << endl;
	//}
}



void microphone_input2()
{
	// Check that the device can capture audio
	if (sf::SoundRecorder::isAvailable() == false)
	{
		std::cout << "Sorry, audio capture is not supported by your system" << std::endl;
		exit(0);
	}

	// Choose the sample rate
	unsigned int sampleRate;
	std::cout << "Please choose the sample rate for sound capture (44100 is CD quality): ";
	std::cin >> sampleRate;
	std::cin.ignore(10000, '\n');

	// Wait for user input...
	std::cout << "Press enter to start recording audio";
	std::cin.ignore(10000, '\n');

	// Here we'll use an integrated custom recorder, which saves the captured data into a SoundBuffer
	sf::SoundBufferRecorder recorder;

	// Audio capture is done in a separate thread, so we can block the main thread while it is capturing
	recorder.start(sampleRate);
	std::cout << "Recording... press enter to stop";
	std::cin.ignore(10000, '\n');
	recorder.stop();

	// Get the buffer containing the captured data
	const sf::SoundBuffer& buffer = recorder.getBuffer();

	// Display captured sound informations
	std::cout << "Sound information:" << std::endl;
	std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
	std::cout << " " << buffer.getSampleRate() << " samples / seconds" << std::endl;
	std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;

	// Choose what to do with the recorded sound data
	char choice;
	std::cout << "What do you want to do with captured sound (p = play, s = save) ? ";
	std::cin >> choice;
	std::cin.ignore(10000, '\n');

	if (choice == 's')
	{
		// Choose the filename
		std::string filename;
		std::cout << "Choose the file to create: ";
		std::getline(std::cin, filename);

		// Save the buffer
		buffer.saveToFile(filename);
	}
	else
	{
		// Create a sound instance and play it
		sf::Sound sound(buffer);
		sound.play();

		// Wait until finished
		while (sound.getStatus() == sf::Sound::Playing)
		{
			// Display the playing position
			std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
			std::cout << std::flush;

			// Leave some CPU time for other threads
			sf::sleep(sf::milliseconds(100));
		}
	}

	// Finished!
	std::cout << std::endl << "Done!" << std::endl;

	// Wait until the user presses 'enter' key
	std::cout << "Press enter to exit..." << std::endl;
	std::cin.ignore(10000, '\n');
}

int main()
{
	microphone_input();
	srand(time(NULL));
	overlapsave();
	return 0;
}