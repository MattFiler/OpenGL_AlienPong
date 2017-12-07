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
	PongPAK();
	void FetchFile(std::string requested_file);
	void ClearupFiles();
	
	int getOutputCounter();
	int getCleanupCounter();


private:
	std::string output_array[45];
	int output_counter;
	int cleanup_counter;
};

#endif