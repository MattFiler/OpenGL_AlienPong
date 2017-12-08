#pragma once

#ifndef GAMEVARS_SCORES_H
#define GAMEVARS_SCORES_H

/*
Define our score data
*/
struct pongScores
{
	//In-game scores
	static int p1;
	static int p2;

	//Scoreboard 
	static int scoreboard_p1;
	static int scoreboard_p2;
	static int scoreboard_player;
	static int scoreboard_cpu;
};

#endif