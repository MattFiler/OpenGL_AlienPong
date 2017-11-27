#pragma once
#include <iostream>
#include <string>
#include <fstream>

class PongPAK {
public:
	std::string output_array[45];
	int output_counter;

	PongPAK();
	void PongPAK::FetchFile(std::string requested_file);
	void PongPAK::ClearupFiles();
};