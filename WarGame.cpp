//
//  WarGame.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "WarGame.h"
#include <iostream>
#include <time.h>

using namespace std;

//Boardnode constructor
//inputs: node value
//outpus: boardnode
Boardnode::Boardnode(int newval)
{
    setval(newval);
}

//This function sets a value for the board at the current node 
//inputs: none
//outpus: none
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

//Equals operator for the boardnode
//inputs: boardnode to copy
//outpus: copy of the boardnode
Boardnode& Boardnode::operator=(const Boardnode &other)
{
	value = other.getVal();
	player = other.getPlayer();

    return *this;
}
 

//This function returns the value at the current node 
//inputs: none
//outpus: none
int Boardnode::getVal()	const
{
	return value;
}

//This function returns the player at the current node 
//inputs: none
//outpus: none
int Boardnode::getPlayer() const
{
	return player;
}


//This function changes the boardnode player 
//inputs: player to board change piece to
//outpus: a new game board
void Boardnode::changePlayer(int newplayer)
{
	//make sure valid player
	if(newplayer >= 0 && newplayer <= 2)
		player = newplayer;
}

//This function flips the a piece
//inputs: array with numbers to populate board with
//outpus: a new game board
void Boardnode::flip()
{
    if(player == GREEN)
        player = BLUE;
    
    else if(player == BLUE)
        player = GREEN;
}


//board constructor 
//inputs: array with numbers to populate board with
//outpus: a new game board
Board::Board(int values[6][6])
{
    build(values);
}

//This function initializes the game board and assings all player assignments to 0 (empty)
//inputs: array with numbers to populate board with
//outpus: none
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
//inputs: board to copy
//outpus: copy of the given board
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

//This function returns the value of the board spot given by the coordinates
//inputs: coordinates
//outpus: value of board piece
int Board::getVal(int x, int y)
{
	return board[x][y].getVal();
}

//This function returns the number of remaining moves left in the game
//inputs: none
//outpus: number of remaining moves
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

//This function computes the score of the blue (first) player 
//inputs: none
//outpus: blue's score
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

//This function computes the score of the green (second) player
//inputs: none
//outpus: green's score
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

//This function computes the evaluation function used by minimax and alpha-beta agents
//inputs: none
//outpus: evaluation function
int Board::eval()
{
    return (getBlueScore() - getGreenScore());
}

//This function changes player on the board to the given player
//inputs: player to change to and the coordinates of where to place it
//outpus: none
void Board::changePlayer(int player, int x, int y)
{
    //if out of bounds then return
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return;
    
	(board[x][y]).changePlayer(player);
}

//This function returns the player at the specified coordinates
//inputs: coordinates of player to return
//outpus: player at given point
int Board::getPlayer(int x, int y)
{
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return OUT;
    else
        return board[x][y].getPlayer();
}

//This function flips the player at the specified coordinates
//inputs: coordinates of player to flip
//outpus: none
void Board::flipPlayer(int x, int y)
{
    if((x < 0)||(x > 5)||(y < 0)||(y > 5))
        return;
    
    board[x][y].flip();
}

//This function prints the current board
//inputs: none
//outpus: none
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
    cout << "_________________________" << endl;
    cout << "0\t1\t2\t3\t4\t5"<< endl;
    
}

//This function allows the minimax and alpha-beta players to move. Both M1 Death Blitz and Commando Para Drop cases are covered here
//inputs: current player and its coordinates
//outpus: updated board
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

//This function allows the 'chance' player to move. The 'chance' agent can only flip enemy pieces if the 'coin toss' is 1
//inputs: current player and its coordinates
//outpus: updated board
int Board::moveChance(int player, int x, int y)
{
    //if space is already taken then return
    if( (board[x][y].getPlayer() != 0) ||(x > 5 )||(x < 0) ||(y > 5 )||(y < 0))
        return -1;
    
    //else in empty space sp place coresponding player there
    changePlayer(player, x, y);
    
    
    if(rand() % 2== 0)
    {
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
    int ncompFlag = false; // false until there are multiple nodes on current level
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
                
                
                //see if this current node can be pruned
                if(compFlag)
                {
                    if(player == MAXP)//if the player is a max
                    {
                       if(abresult > compVal)// and it finds a larger value than the compare value then return since
                           return abresult; // this means that the parent node to this already has a better option then the current path
                    }
                    else if(player == MINP)
                    {
                        if(abresult < compVal)// and it finds a smaller value than the compare value then return since
                            return abresult; // this means that the parent node of teh parent node (grandparent node) to this
                                            //already has a better option then the current path so terminate this path
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



//This is the function used to start the game. It reads in the players (human, minimax, alpha-beta, chance) and calls another function that allows agents to actually play the game
//inputs: none
//outpus: none
Board WarWorld::startGame()
{
    int p1type = -1;

    time1 = time2 = 0;

    while(p1type < 0)
    {
        cout << "Enter player 1 type (Enter: 1-human  2-MinMax  3-AlphaBeta 4-ChanceAB)" << endl;
        cin >> p1type;
        if ((p1type) < 1 || (p1type > 4))
            p1type = -1;
    }
    
    
    int p2type = -1;
    while(p2type < 0)
    {
        cout << "Enter player 2 type (Enter: 1-human  2-MinMax  3-AlphaBeta 4-ChanceAB)" << endl;
        cin >> p2type;
        if ((p2type) < 1 || (p2type > 4))
            p2type = -1;
    }
    
    int exp1 =0;
    int exp2 =0;
    Board temp = game(p1type,p2type,exp1,exp2);
    
    //print our the final board
    cout << "_____________________________________________" << endl << "FINAL GAME STATE" << endl << endl;
    temp.print();
    cout << endl;
    
    
    if(p1type == HUMAN)
        cout << "Human\t\t";
    else if(p1type == MINMAX)
        cout << "MinMax\t\t";
    else if(p1type == ABP)
        cout << "AlphaBeta\t";
    

    cout << "Player-1-Blue \tScore: " << temp.getBlueScore() << "\t\tNodes: " << exp1 << "\tTime/move " << time1/18 <<endl << endl;

    
    if(p2type == HUMAN)
        cout << "Human\t\t";
    else if(p2type == MINMAX)
        cout << "MinMax\t\t";
    else if(p2type == ABP)
        cout << "AlphaBeta\t";
    

    cout << "Player-2-Green \tScore: " << temp.getGreenScore() << "\t\tNodes: " << exp2<< "\tTime/move " << time2/18  << endl << endl;

    
    
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

    return temp;

}

//This function allows each agent to take turns playing the game. The function used to evaluate each move is agent-dependent
//inputs: each player and how many nodes each has expanded
//outpus: a new board including the most recent move
Board WarWorld::game(int player1, int player2, int & p1expanded, int & p2expanded)
{
    Board currB = board;
    while(currB.getRemainingMoves() > 0)
    {

        clock_t temp1 = clock();

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
            cout << "AlphaBeta BLUE moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        else if(player1 == CHANCEAB)
        {
            int x = -7;
            int y = -7;
            
            AlphaBeta(currB, P1, 0, 4, p1expanded, x, y,0,false);
            currB.moveChance(P1, x, y);
            currB.print();
            cout << "CAlphaBeta BLUE moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        time1 += ((float)clock() - (float)temp1) / CLOCKS_PER_SEC;
        
        
        
        

        clock_t temp2 = clock();
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
            cout << "AlphaBeta GREEN moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        else if(player2 == CHANCEAB)
        {
            int x = -7;
            int y = -7;
            
            AlphaBeta(currB, P2, 0, 4, p2expanded, x, y,0,false);
            currB.moveChance(P2, x, y);
            currB.print();
            cout << "CAlphaBeta GREEN moved to location X: " << x << "  Y: " << y << endl << endl;
            
        }
        time2 += ((float)clock() - (float)temp2) / CLOCKS_PER_SEC;
        
        
    }//while game is playing
    
    
    return currB;
}





