//
//  CSP.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "CSP.h"

vector<string>&  DataBase::operator[] (const string nString)
{
    return data[hash(nString)];
}

int DataBase::hash(string s)
{
    
}

DataBase::DataBase()
{
    ifstream curr;
    string temp;
    
    data.resize(50);
    curr.open("wordlists/adjective.txt");
    
    while(!curr.eof() )
    {
        curr >> temp;
        data[hash("adjective")].push_back(temp);
    }
    
}