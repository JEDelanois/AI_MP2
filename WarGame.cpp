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

    return *this;

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
            if ((board[i][j]).getPlayer() == GREEN){
                int temp = (board[i][j]).getVal();
                score +=temp;
            }
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
        cout << "|\t" << y;
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
        cout << "|";
        cout << endl << endl;
    }
    cout << "___________________________" << endl;
    cout << "0\t1\t2\t3\t4\t5"<< endl;
    
}


int Board::move(int player, int x, int y)
{
    //if space is already taken then return
    if( (board[x][y].getPlayer() != 0) ||(x > 5 )||(x < 0) ||(y > 5 )||(y < 0))
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

/*
 currboard - current game state
 cur depth - current depth into the local tree
 finaldepth- final depth search of the tree
 total_expaneded_nodes = how many nodes are searched
 
 selx and sely are the cordinates that the current min max player will put there piece this is 
 so that when the game function calls this it can aquire its next move
 */
int WarWorld::MinMax(Board currBoard,int player ,int currdepth, int finaldepth, int & total_expanded_nodes,int & selx, int & sely)
{
    
    //if at final depth then return the board or end game
    if((currdepth == finaldepth) || (currBoard.getRemainingMoves() == 0))
    {
        total_expanded_nodes++;
        return currBoard.eval();
    }
    
    //count current node as expanded
    total_expanded_nodes++;
    
    //all these holde the data for all the child nodes
    vector<int> xvals;
    vector<int> yvals;
    vector<int> MinMaxvals;
    
    for(int y = 0; y < 6; y++)
    {
        for(int x = 0; x < 6; x++)
        {
            // if there is no pice place one there to see
            if(currBoard.getPlayer(x, y) == NONE)
            {
                // save the MinMax value and the move that it was associated with
                xvals.push_back(x);
                yvals.push_back(y);
                
                //copy board and make the next move
                Board temp = currBoard;
                temp.move(player, x, y);
                
                int tplayer;
                if(player == GREEN)
                    tplayer = BLUE;
                else
                    tplayer = GREEN;
                
                //only care about these in the game not in any of the recursive min max calls
                int tx = 0;
                int ty = 0;
                
                MinMaxvals.push_back( MinMax(temp, tplayer, currdepth +1, finaldepth, total_expanded_nodes, tx, ty) );
            }
                
        }
    }
    
    //assume first index for comparison
    int tidx = 0;
    int temp = MinMaxvals[0];
    //if max player return max value
    if(player == MAXP)
    {
        for(int i = 0; i < MinMaxvals.size(); i++)
        {
            if(MinMaxvals[i] > temp)//if found new max
            {
                temp = MinMaxvals[i]; //set new value
                tidx = i; // then save new index asmax
            }
        }
    }
    
    else// else min player so return min values
    {
        for(int i = 0; i < MinMaxvals.size(); i++)
        {
            if(MinMaxvals[i] < temp)//if found new max
            {
                temp = MinMaxvals[i]; //set new value
                tidx = i; // then save new index asmax
            }

        }
        
    }
    
    //pass back the xy vals for the game to make next move
    selx = xvals[tidx];
    sely = yvals[tidx];
    
    //and return the value of the node to parents
    
    return MinMaxvals[tidx];
}


/*
 currboard - current game state
 cur depth - current depth into the local tree
 finaldepth- final depth search of the tree
 total_expaneded_nodes = how many nodes are searched
 
 selx and sely are the cordinates that the current min max player will put there piece this is
 so that when the game function calls this it can aquire its next move
 
compFlag signifies if the comp val given is valid. on first calls there no no value to compare so you need to ignore flag so make FALSE!
 */
int WarWorld::AlphaBeta(Board currBoard,int player ,int currdepth, int finaldepth, int & total_expanded_nodes,int & selx, int & sely, int compVal, bool compFlag)
{
    
    //if at final depth then return the board or end game
    if((currdepth == finaldepth) || (currBoard.getRemainingMoves() == 0))
    {
        total_expanded_nodes++;
        return currBoard.eval();
    }
    
    //count current node as expanded
    total_expanded_nodes++;
    
    //all these holde the data for all the child nodes
    vector<int> xvals;
    vector<int> yvals;
    vector<int> MinMaxvals;
    
    //comparison value for  pruning
    int ncompval = 0;
    int ncompFlag = false; // always need to fully expand first children
    for(int y = 0; y < 6; y++)
    {
        for(int x = 0; x < 6; x++)
        {
            // if there is no pice place one there to see
            if(currBoard.getPlayer(x, y) == NONE)
            {
                // save the MinMax value and the move that it was associated with
                xvals.push_back(x);
                yvals.push_back(y);
                
                //copy board and make the next move
                Board temp = currBoard;
                temp.move(player, x, y);
                
                int tplayer;
                if(player == GREEN)
                    tplayer = BLUE;
                else
                    tplayer = GREEN;
                
                //only care about these in the game not in any of the recursive min max calls
                int tx = 0;
                int ty = 0;
                
                
                int abresult = AlphaBeta(temp, tplayer, currdepth +1, finaldepth, total_expanded_nodes, tx, ty,ncompval, ncompFlag);
                
                MinMaxvals.push_back( abresult );
                
                
                //see if this current node needs to be pruned
                if(compFlag)
                {
                    if(player == MAXP)
                    {
                       if(abresult < compVal)// if found a lower value return and stop expanding sibling does
                           return abresult;
                    }
                    else if(player == MINP)
                    {
                        if(abresult > compVal)// if found a higher value return and stop expanding sibling does
                            return abresult;
                    }
                    
                }
                
                //set comparison value for its child nodes!!!
                if( player == MAXP )// set comparison value for max players
                {
                    if( (ncompFlag == false) || (abresult > compVal) )//if first iteration or new max
                    {
                        ncompval = abresult;
                    }
                }
                else if(player == MINP)// set comparison value for min players
                {
                    if( (ncompFlag == false) || (abresult < compVal) )//if first iteration or new min
                    {
                        ncompval = abresult;
                    }
                }
                //we now have atleast one val to compare for next nodes so make sure to tell next iterations to compare
                ncompFlag = true;
            }
            
        }
    }
    
    //assume first index for comparison
    int tidx = 0;
    int temp = MinMaxvals[0];
    //if max player return max value
    if(player == MAXP)
    {
        for(int i = 0; i < MinMaxvals.size(); i++)
        {
            if(MinMaxvals[i] > temp)//if found new max
            {
                temp = MinMaxvals[i]; //set new value
                tidx = i; // then save new index asmax
            }
        }
    }
    
    else// else min player so return min values
    {
        for(int i = 0; i < MinMaxvals.size(); i++)
        {
            if(MinMaxvals[i] < temp)//if found new max
            {
                temp = MinMaxvals[i]; //set new value
                tidx = i; // then save new index asmax
            }
            
        }
        
    }
    
    //pass back the xy vals for the game to make next move
    selx = xvals[tidx];
    sely = yvals[tidx];
    
    //and return the value of the node to parents
    
    return MinMaxvals[tidx];
}




void WarWorld::startGame()
{
    int p1type = -1;
    while(p1type < 0)
    {
        cout << "Enter player 1 type (Enter: 1-human  2-MinMax  3-AlphaBeta)" << endl;
        cin >> p1type;
        if ((p1type) < 1 || (p1type > 3))
            p1type = -1;
    }
    
    
    int p2type = -1;
    while(p2type < 0)
    {
        cout << "Enter player 2 type (Enter: 1-human  2-MinMax  3-AlphaBeta)" << endl;
        cin >> p2type;
        if ((p2type) < 1 || (p2type > 3))
            p2type = -1;
    }
    
    int exp1 =0;
    int exp2 =0;
    Board temp = game(p1type,p2type,exp1,exp2);
    
    //print our the final board
    temp.print();
    
    cout << "Player 1 Blue \tScore: " << temp.getBlueScore() << "\tNodes: " << exp1 << endl;
    cout << "Player 2 Green \tScore: " << temp.getGreenScore() << "\tNodes: " << exp2 << endl;
    
    
    if(temp.eval() > 0)
    {
        cout << "Blue Wins!!!!!" << endl;
    }
    else if(temp.eval() < 0)
    {
        cout << "Green Wins!!!!" << endl;
    }
    else
    {
        cout << " Tie Game :(" << endl;
    }

}


Board WarWorld::game(int player1, int player2, int & p1expanded, int & p2expanded)
{
    Board currB = board;
    while(currB.getRemainingMoves() > 0)
    {
        //make player one go first
        if(player1 == HUMAN)
        {
            int x = -1;
            int y = -1;
            int status = -1;
            
            while(status < 0)
            {
                while((x < 0) || (y < 0))
                {
                    currB.print();
                    cout << "Player 1 make your move (Enter: X Y)" << endl;
                    cin >> x >> y;
                   
                    if(x > 5)
                        x = -1;
                    if(y > 5)
                        y = -1;
                    
                }
                //make sure its a valid move
                status = currB.move(P1, x, y );
                x = y = -1; //if there is an error these need to be negative
            }
            
        }
        else if(player1 == MINMAX)
        {
            int x = -7;
            int y = -7;
            
            MinMax(currB, P1, 0, 4, p1expanded, x, y);
            currB.move(P1, x, y);
            currB.print();
            cout << "MinMax BLUE moved to location X: " << x << "  Y: " << y << endl << endl;
        
        }
        else if(player1 == ABP)
        {
            int x = -7;
            int y = -7;
            
            AlphaBeta(currB, P1, 0, 4, p1expanded, x, y,0,false);
            currB.move(P1, x, y);
            currB.print();
            cout << "MinMax BLUE moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        
        
        
        
        
        
        //player 2 moves
        if(player2 == HUMAN)
        {
            int x = -1;
            int y = -1;
            int status = -1;
            
            while(status < 0)
            {
                while((x < 0) || (y < 0))
                {
                    currB.print();
                    cout << "Player 2 make your move (Enter: X Y)" << endl;
                    cin >> x >> y;
                    
                    if(x > 5)
                        x = -1;
                    if(y > 5)
                        y = -1;
                    
                }
                //make sure its a valid move
                status = currB.move(P2, x, y );
                x = y = -1; //if there is an error these need to be negative
            }
        }
        else if(player2 == MINMAX)
        {
            int x = -7;
            int y = -7;
            
            MinMax(currB, P2, 0, 4, p2expanded, x, y);
            currB.move(P2, x, y);
            currB.print();
            cout << "MinMax GREEN moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        else if(player2 == ABP)
        {
            int x = -7;
            int y = -7;
            
            AlphaBeta(currB, P2, 0, 4, p2expanded, x, y,0,false);
            currB.move(P2, x, y);
            currB.print();
            cout << "MinMax GREEN moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        
        
        
        
    }//while game is playing
    
    
    return currB;
}





