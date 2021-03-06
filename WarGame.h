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
#include <time.h>
#include <vector>
#include <time.h>

#endif /* defined(__AI_MP2__WarGame__) */

#define BLUE 1
#define GREEN 2
#define NONE 0
#define OUT 3

#define MAXP 1
#define MINP 2

#define P1 1
#define P2 2

#define HUMAN 1
#define MINMAX 2
#define ABP 3
#define CHANCEAB 4

#define MMDEPTH 3
#define ABPDEPTH 4


class Boardnode
{
public:
    Boardnode(){}
	Boardnode(int value);	//constructor
    void setval(int newval);
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
    Board(){}
	Board(int values[6][6]);	//constructor with array of values to fill in
    void build(int values[6][6]);
	Board& operator=(const Board &other);	//'equals' overload operator
	int getRemainingMoves();	//calculates remaining moves left in the game
	int getBlueScore();
	int getGreenScore();
    int getVal(int x, int y);
    int getPlayer(int x, int y);
    int move(int player, int x, int y);
    void flipPlayer(int x, int y);
    void print();
    int moveChance(int player, int x, int y);
    
    //evaluation function for the current game state blue - green
    int eval();
    
	 
	
private:
	Boardnode board[6][6];
    void changePlayer(int player, int x, int y);

};


class WarWorld
{
public:
    WarWorld(){}
    Board board;
    void build(int values[6][6]);
    Board startGame(int p1type, int p2type,bool Psteps );// enter -1 for p1 and p2 to prompt user for player types
	float time_p1, time_p2;
    
private:
    float time1;
    float time2;
    Board game(int player1, int player2, int & p1expanded, int & p2expanded,bool Psteps);
    
    
    //player 1 is blue and MAX  ----  player two in green and MIN
    //player represents what whos current turn it is
    int MinMax(Board currBoard, int player ,int currdepth, int finaldepth, int & total_expanded_nodes,int & selx, int & sely);
    
    int AlphaBeta(Board currBoard,int player ,int currdepth, int finaldepth, int & total_expanded_nodes,int & selx, int & sely, int compVal, bool compFlag);
    
};


