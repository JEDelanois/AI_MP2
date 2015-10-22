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


Boardnode& Boardnode::operator=(const Boardnode &other)
{
	value = other.getVal();
	player = other.getPlayer();

    return *this;
}
 



//returns value
int Boardnode::getVal()	const
{
	return value;
}

//returns player
int Boardnode::getPlayer() const
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

void Boardnode::flip()
{
    if(player == GREEN)
        player = BLUE;
    
    else if(player == BLUE)
        player = GREEN;
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

//'equals' overload operator for 'Board' class
Board& Board::operator=(const Board &other)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			(board[i][j]) = other.(board[i][j]);	//create new node with value from array and i,j coordinates
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
    //if out of bounds then return
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return;
    
	(board[x][y]).changePlayer(player);
}

int Board::getPlayer(int x, int y)
{
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return OUT;
    else
        return board[x][y].getPlayer();
}


void Board::flipPlayer(int x, int y)
{
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return;
    
    board[x][y].flip();
}

int Board::move(int player, int x, int y)
{
    //if space is already taken then return
    if((board[x][y].getPlayer() != 0)||(x > 5 )||(x < 0) ||(y > 5 )||(y < 0))
        return -1;
    
    //else in empty space sp place coresponding player there
    changePlayer(player, x, y);
    
    //if there is a player on the same team around
    if((getPlayer(x-1, y) == player)||(getPlayer(x, y-1) == player)||(getPlayer(x+1, y) == player)||(getPlayer(x, y+1) == player))
    {
        //flip other oponent pieces
        if( (getPlayer(x-1, y) != NONE )&& (getPlayer(x-1, y) != OUT) && (getPlayer(x-1, y) != player) )
           flipPlayer(x-1,y);
        
        if( (getPlayer(x+1, y) != NONE )&& (getPlayer(x+1, y) != OUT) && (getPlayer(x+1, y) != player) )
            flipPlayer(x+1,y);
        
        if( (getPlayer(x, y-1) != NONE )&& (getPlayer(x, y-1) != OUT) && (getPlayer(x, y-1) != player) )
            flipPlayer(x,y-1);
        
        if( (getPlayer(x, y+1) != NONE )&& (getPlayer(x, y+1) != OUT) && (getPlayer(x, y+1) != player) )
            flipPlayer(x,y+1);
           
    }
        
    
   
    return 1;
}





