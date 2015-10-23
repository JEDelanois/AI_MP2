//
//  main.cpp
//  AI_MP2
//
//  Created by Erik and Dallas.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include <iostream>
#include "CSP.h"
#include "WarGame.h"



int main(int argc, const char * argv[]) {
   // CSTworld temp( "/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/CSTproblems/prob1.txt" ,"/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/wordlists/");
    
    
    //cout << temp.parameters.data.printAll() << endl << endl;
    
   // temp.parameters.print();
    //
    //cout << endl <<endl << endl;
    

    //temp.LetterSearch();
    
    //create random board
    int temp[6][6];
    srand(60);
    
    for(int x = 0; x<6; x++)
    {
        for(int y = 0; y<6; y++)
        {
            temp[x][y] = rand()%100;
        }
    }
    WarWorld world;
    
    world.build(temp);
    world.startGame();

    return 0;
}
