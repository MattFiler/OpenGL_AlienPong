#include "PongPAK.h"
#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>  

PongPAK::PongPAK() 
{
	//output_array = { " " };
	output_counter = 0;
}

/*
	Fetch requested file from PongPAK
*/
void PongPAK::FetchFile(std::string requested_file)
{
	//Make directory
	_mkdir("Resources_Temp");

	//Get file position in PAK from manifest
	std::string manifest_line;
	std::ifstream pong_manifest(".\\Resources\\resources.pongmfst");

	int file_starting_position = 0;
	int file_ending_position = 0;
	int file_length = 0;
	int lines_to_capture = 0;
	while (getline(pong_manifest, manifest_line))
	{
		if (lines_to_capture > 0)
		{
			if (lines_to_capture == 2) {
				file_starting_position = atoi(manifest_line.c_str());
			}
			if (lines_to_capture == 1) {
				file_ending_position = atoi(manifest_line.c_str());
			}
			lines_to_capture -= 1;
		}
		if (manifest_line == requested_file)
		{
			lines_to_capture = 2;
		}
	}
	file_length = file_ending_position - file_starting_position;

	//Fetch file from PAK
	std::ifstream pong_pak(".\\Resources\\resources.pongpak", std::ifstream::binary);
	pong_pak.seekg(file_starting_position, std::ios::cur);
	char* read_file_from_pongpak = new char[file_length];
	pong_pak.read(read_file_from_pongpak, file_length);

	//Create new file from PAK
	std::ofstream output_file("Resources_Temp\\" + requested_file, std::ofstream::binary);
	output_file.write(read_file_from_pongpak, file_length);
	output_array[output_counter] = requested_file;
	output_counter += 1;

	//Clean up
	delete[] read_file_from_pongpak;
	pong_manifest.close();
	pong_pak.close();
	output_file.close();
}

/*
	Clear up any files exported from PongPAK
*/
void PongPAK::ClearupFiles(void)
{
	for (int i = 0; i <= output_counter; i++)
	{
		remove(("Resources_Temp\\" + output_array[i]).c_str());
	}
}