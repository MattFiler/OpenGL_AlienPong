#pragma once
#include <iostream>
#include <string>
#include <fstream>



/*

//////// PONG - Created by Matt Filer ////////
/////////////// PongPAK HEADER ///////////////

*/



class PongPAK 
{
public:
	std::string output_array[45];
	int output_counter;
	int cleanup_counter;

	PongPAK();
	void PongPAK::FetchFile(std::string requested_file);
	void PongPAK::ClearupFiles();
};