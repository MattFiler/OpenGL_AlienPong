#include "../structs.h"

#ifndef DEFINE_ALIENPONG_SCORES
#define DEFINE_ALIENPONG_SCORES

/* 
	Set all pongScores values
*/

//In-game Scores
int pongScores::p1 = 0;
int pongScores::p2 = 0;

//Scoreboard Scores
int pongScores::scoreboard_p1 = 0;
int pongScores::scoreboard_p2 = 0;
int pongScores::scoreboard_player = 0;
int pongScores::scoreboard_cpu = 0;

#endif