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

#define BLUE 1
#define GREEN 2
#define NONE 0
#define OUT 3

class Boardnode
{
public:
    Boardnode(){}
	Boardnode(int value);	//constructor
	Boardnode& operator=(const Boardnode &other); //equals operator

    int getVal() const;				//get value of coordinates
    int getPlayer() const;	//get player of coordinates
	void changePlayer(int newplayer);	//changes player on the given piece
    void flip(); //flips the player

    
private:
	int value;				//value of boardnode number
	int player;				// 0 is no player, 1 is blue player, 2 is green player

};



class Board
{
public:
	Board(int ** values);	//constructor with array of values to fill in
	int getRemainingMoves();	//calculates remaining moves left in the game
	int getBlueScore();
	int getGreenScore();
    int getVal(int x, int y);
    int getPlayer(int x, int y);
    int move(int player, int x, int y);
    void flipPlayer(int x, int y);
	
private:
	Boardnode board[6][6];
    void changePlayer(int player, int x, int y);

};


class WarWorld
{
public:
    
private:
    
};


