#pragma once

#ifndef GAMEVARS_SCORES_H
#define GAMEVARS_SCORES_H

class GameVars_Scores
{
public:
	//Main void
	GameVars_Scores();

	//In-game scores
	int p1;
	int p2;

	//Scoreboard 
	int scoreboard_p1;
	int scoreboard_p2;
	int scoreboard_player;
	int scoreboard_cpu;
};

#endif