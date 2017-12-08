#pragma once
#include <iostream>
#include <fstream>
#include <direct.h>  
#include <string>
#include "AlienPong/Core/structs.h"

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

	void readScoreboard();
	void saveScoreboard();


private:
	//Pong scores
	pongScores pong_scores;

	std::string output_array[45];
	int output_counter;
	int cleanup_counter;
};

#endif