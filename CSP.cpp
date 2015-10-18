//
//  CSP.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "CSP.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <dirent.h>

using namespace std;

vector<string>&  DataBase::operator[] (const string nString)
{
    return data[hash(nString)];
}

int DataBase::hash(string s)
{
    int i;
    for( i = 0; i < CatNames.size(); i++)
    {
        if(s == CatNames[i])
            break;
    }
    return i;
}

DataBase::DataBase(string path)
{
    string temp;
   
   
    CatNames.push_back("animal");
    CatNames.push_back("color");
    CatNames.push_back("computer");
    CatNames.push_back("noun");
    CatNames.push_back("verb");
    CatNames.push_back("transportation");
    CatNames.push_back("food");
    CatNames.push_back("furniture");
    CatNames.push_back("game");
    CatNames.push_back("clothing");
    CatNames.push_back("music");
    CatNames.push_back("kitchen");
    CatNames.push_back("nature");
    CatNames.push_back("math");
    CatNames.push_back("job");
    CatNames.push_back("health");
    CatNames.push_back("adverb");
    CatNames.push_back("container");
    CatNames.push_back("number");
    CatNames.push_back("language");
    CatNames.push_back("emotion");
    CatNames.push_back("palindrome");
    CatNames.push_back("body");
    CatNames.push_back("family");
    CatNames.push_back("conjunction");
    CatNames.push_back("shape");
    CatNames.push_back("pronoun");
    CatNames.push_back("money");
    CatNames.push_back("interjection");
    CatNames.push_back("adjective");
    
    //make the array size match the size of the numbe of categorys
    // so that all indexes match up with the hash function this is needed!!
    data.resize(CatNames.size());
    
    for(int i = 0; i < CatNames.size() ; i++)
    {
        string a = CatNames[i];
        ifstream curr;
        curr.open(path + CatNames[i] + ".txt");
        if(curr.is_open())
        {
            while(!curr.eof() )
            {
                curr >> temp;
                data[hash(CatNames[i])].push_back(temp);
            }
            
            curr.close();
            curr.clear();
        }
        
        else
        {
            cout << "Error opening file: " << CatNames[i] << endl;
        }
        curr.clear();
    }
   
    
}


string DataBase::printAll()
{
    string s;
    for(int a = 0; a < data.size(); a++)
    {
        s += CatNames[a] + " _____________________\n";
        for(int i = 0; i< data[a].size(); i++)
        {
            s+= data[a][i] + "\n";
        }
    }
    
    
    return s;
}


