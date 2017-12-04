#pragma once
#include <iostream>
#include <fstream>
#include <direct.h>  
#include <string>

#ifndef PONGPAK_H
#define PONGPAK_H

/*
PongPAK
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

#endif