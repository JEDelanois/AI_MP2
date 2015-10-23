//
//  WarGame.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "WarGame.h"
#include <iostream>

using namespace std;

//Boardnode constructor
Boardnode::Boardnode(int newval)
{
    setval(newval);
}


void Boardnode::setval(int newval)
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
Board::Board(int values[6][6])
{
    build(values);
}

void Board::build(int values[6][6])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
            board[i][j].setval(values[i][j]);	//create new node with value from array and i,j coordinates
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
			board[i][j] = other.board[i][j];	//create new node with value from array and i,j coordinates
		}
	}

<<<<<<< HEAD
	return *this;
=======
    return *this;

>>>>>>> 3d7d073b5a98f4962aea9df7f210da5b9797d47c
}


int Board::getVal(int x, int y)
{
	return board[x][y].getVal();
}

int Board::getRemainingMoves()
{
	int moves = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if ((board[i][j]).getPlayer() == NONE)
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

int Board::eval()
{
    return (getBlueScore() - getGreenScore());
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


void Board::print()
{
    for(int y = 0; y < 6; y++)
    {
        //for each row
        for(int x = 0; x < 6; x++)
        {
            cout << getVal(x, y) << "\t";
        }
        cout << endl;
        //for each row print out the player
        for(int x = 0; x < 6; x++)
        {
            if(getPlayer(x, y) == GREEN)
                cout << "G";
            
            if(getPlayer(x, y) == BLUE)
                cout << "B";
            
            cout << "\t";
        }
        cout << endl << endl;
    }
    
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



void WarWorld::build(int values[6][6])
{
    board.build(values);
}


int WarWorld::MinMax(Board currBoard,int player ,int currdepth, int finaldepth, int & total_expanded_nodes,int & selx, int & sely)
{
    //if at final depth then return the board or end game
    if((currdepth == finaldepth) || (currBoard.getRemainingMoves() == 0))
    {
        total_expanded_nodes++;
        return currBoard.eval();
    }
    
    
    total_expanded_nodes++;
    for(int y = 0; y < 6; y++)
    {
        for(int x = 0; x < 6; x++)
        {
            // if there is no pice place one there to see
            if(currBoard.getPlayer(x, y) == NONE)
            {
                // call function and save x y
            }
                
        }
    }
    
    // pass back appropriate x y value and return proper value acording to min max
    
}









