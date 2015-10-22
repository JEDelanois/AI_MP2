//
//  WarGame.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "WarGame.h"

//Boardnode constructor
Boardnode::Boardnode(int newval)
{
	value = newval;
	player = 0;

	//boundary checking
	if (newval < 0)
		value = 0;
	if (newval > 99)
		value = 99;
}

void Boardnode::operator=(const Boardnode & obj){}
/*
{
	value = obj.getVal();
	player = obj.getPlayer();
	x = obj.getX();
	y = obj.getY();
    
}
 
 */


//returns value
int Boardnode::getVal()	
{
	return value;
}

//returns player
int Boardnode::getPlayer() 
{
	return player;
}


//changes the boardnode player
void Boardnode::changePlayer(int newplayer)
{
	//make sure valid player
	if(newplayer >= 0 && newplayer <= 2)
		player = newplayer;
}


//constructor initializes board values to array vals, and assings all player assignments to 0 (empty)
Board::Board(int ** values)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			(board[i][j]) = Boardnode(values[i][j]);	//create new node with value from array and i,j coordinates
		}
	}

}

int Board::getVal(int x, int y)
{
	return (board[x][y]).getVal();
}

int Board::getRemainingMoves()
{
	int moves = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if ((board[i][j]).getPlayer() == 0)
				moves++;
		}
	}
	return moves;
}

int Board::getBlueScore()
{
	int score = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
            if ((board[i][j]).getPlayer() == BLUE)
				score += (board[i][j]).getVal();
		}
	}

	return score;
}

int Board::getGreenScore()
{
	int score = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if ((board[i][j]).getPlayer() == GREEN)
				score += (board[i][j]).getVal();
		}
	}

	return score;
}

//change player on the board to the given player
void Board::changePlayer(int player, int x, int y)
{
	(board[x][y]).changePlayer(player);
}



int Board::move(int player, int x, int y)
{
    //if space is already taken then return
    if(board[x][y].getPlayer() != 0)
        return -1;
    
    //else in empty space sp place coresponding player there
    changePlayer(player, x, y);
    
    //if there is a player on the same team around then check to see if
    if(board[x-1])
    
   
    return 1;
}





