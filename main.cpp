//
//  main.cpp
//  AI_MP2
//
//  Created by Erik and Dallas.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "CSP.h"
#include "WarGame.h"




int main(int argc, const char * argv[]) {




   // CSTworld cst( "/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/CSTproblems/prob2.txt" ,"/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/wordlists/");
   CSTworld cst("C:/Users/Dallas/Documents/CS 440/AI_MP2/CSTproblems/prob2.txt", "C:/Users/Dallas/Documents/CS 440/AI_MP2/wordlists/");
    
    cst.WordSearch();
    
    cout << endl <<endl << endl;
    
    cst.LetterSearch();
    
    
	
	

	

    //cout << temp.parameters.data.printAll() << endl << endl;
    
    //temp.parameters.print();
    
    //cout << endl <<endl << endl;
    
	//temp.WordSearch();
   // temp.LetterSearch();

    
    //create random board

	ifstream mapfile;

	//CHANGE YOUR PATH HERE
	mapfile.open("C:/Users/Dallas/Documents/CS 440/AI_MP2/Maps/Narvik.txt");

    int temp[6][6];

    
    srand(303);


    
    for(int x = 0; x<6; x++)
    {
        for(int y = 0; y<6; y++)
        {
          // temp[x][y] = rand()%100;
		mapfile >> temp[x][y];		//reads in given board
        }
    }
    WarWorld world;
    
    //world.build(temp);


    //world.startGame();
	int a;
	cin >> a;


	mapfile.close();
    return 0;
}
