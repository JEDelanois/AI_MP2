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




void fillArray(string path, int temp[6][6])
{
    ifstream mapfile;
    mapfile.open(path);
    
    for(int x = 0; x<6; x++)
    {
        for(int y = 0; y<6; y++)
        {
            
            mapfile >> temp[x][y];		//reads in given board
        }
    }
    mapfile.close();
}


void fillArrayRand(string path, int temp[6][6])
{
    srand((unsigned int)clock());
    
    for(int x = 0; x<6; x++)
    {
        for(int y = 0; y<6; y++)
        {
            
            temp[x][y] = rand()%100;		//reads in given board
        }
    }
    
}



int main(int argc, const char * argv[]) {





   // CSTworld cst( "/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/CSTproblems/prob2.txt" ,"/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/wordlists/");
   //CSTworld cst("C:/Users/Dallas/Documents/CS 440/AI_MP2/CSTproblems/prob2.txt", "C:/Users/Dallas/Documents/CS 440/AI_MP2/wordlists/");

    
    //cst.WordSearch();
    
    //cout << endl <<endl << endl;
    
    //cst.LetterSearch();
    
    
	
	

	

    //cout << temp.parameters.data.printAll() << endl << endl;
    
    //temp.parameters.print();
    
    //cout << endl <<endl << endl;
    
	//temp.WordSearch();
   // temp.LetterSearch();

    
    //create random board


	//CHANGE YOUR PATH HERE
	//mapfile.open("C:/Users/Dallas/Documents/CS 440/AI_MP2/Maps/Narvik.txt");

    
    
    int temp[6][6];

    
    
    WarWorld world;
    
    vector<string> maps;
    maps.push_back("/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/Maps/Keren.txt");
    maps.push_back("/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/Maps/Narvik.txt");
    maps.push_back("/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/Maps/Sevastopol.txt");
    maps.push_back("/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/Maps/Smolensk.txt");
    maps.push_back("/Users/Erik/Documents/School/AI/AI_MP2/AI_MP2/Maps/Westerplatte.txt");
    
    vector<Board> sols;

    for (int i = 0; i < (int)maps.size(); i++)
    {
    
        fillArrayRand(maps[i],temp);
        
        
        world.build(temp);
/*
        if(i == 0)
            cout <<"Map Keren:" << endl;
        if(i == 1)
            cout <<"Map Narvik:" << endl;
        if(i == 2)
            cout <<"Map Sevastopol:" << endl;
        if(i == 3)
            cout <<"Map Smolensk:" << endl;
        if(i == 4)
            cout <<"Map Westerplatte:" << endl;
*/
        sols.push_back( world.startGame(4,4,false)) ;
        
        cout << endl << endl << endl;
	
    }
    
    
    
    //int a;
	//cin >> a;


    return 0;
}
