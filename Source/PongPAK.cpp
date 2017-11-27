#include "PongPAK.h"
#include <iostream>
#include <string>
#include <fstream>

PongPAK::PongPAK() 
{
	file_contents = "";
}

void PongPAK::FetchFile(std::string requested_file)
{
	/* GET FILE POSITION IN PAK FROM MANIFEST */
	std::string manifest_line;
	std::ifstream pong_manifest(".\\Resources\\resources.pongmfst");

	int file_starting_position = 0;
	int file_ending_position = 0;
	int file_length = 0;
	int lines_to_capture = 0;
	while (getline(pong_manifest, manifest_line)) 
	{
		if (manifest_line == requested_file)
		{
			lines_to_capture = 2;
		}
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
	}
	file_length = file_ending_position - file_starting_position;


	/* FETCH FILE FROM PAK WITH MANIFEST DATA */
	std::ifstream pong_pak(".\\Resources\\resources.pongmfst", std::ifstream::binary);
	pong_pak.seekg(file_starting_position);
	char* read_file_from_pongpak = new char[file_length];
	pong_pak.read(read_file_from_pongpak, file_length);
	file_contents = read_file_from_pongpak;


	/* USE FILE DATA TO CREATE TEMP FILE */
	//std::ofstream output_file(".\\Resources\\" + requested_file, std::ofstream::binary);
	//output_file.write(read_file_from_pongpak, file_length);


	/* CLEAR UP */
	delete[] read_file_from_pongpak;
	pong_manifest.close();
	pong_pak.close();
	//output_file.close();
}