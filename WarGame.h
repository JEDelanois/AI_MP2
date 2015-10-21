//
//  WarGame.h
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#ifndef __AI_MP2__WarGame__
#define __AI_MP2__WarGame__

#include <stdio.h>
#include <vector>

#endif /* defined(__AI_MP2__WarGame__) */

class Boardnode
{
public:
	Boardnode(int value, int xcoord, int ycoord);	//constructor
	void operator=(const Boardnode & obj); //equals operator

	int getVal();				//get value of coordinates
	int getPlayer();	//get player of coordinates
	int getX();				//x coordinate
	int getY();				//y coordinate
	void changePlayer(int newplayer);	//changes player on the given piece

private:
	int value;				//value of boardnode number
	int player;				// 0 is no player, 1 is blue player, 2 is green player
	int x;
	int y;

};

class Board
{
public:
	Board(int * values);	//constructor with array of values to fill in 
	int getRemainingMoves();	//calculates remaining moves left in the game
	int getBlueScore();
	int getGreenScore();
	void changePlayer(int player, int x, int y);
	
private:
	Boardnode board[6][6];

};


