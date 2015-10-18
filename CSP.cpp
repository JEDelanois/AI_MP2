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
    if (s == "adjective")
        return 0;
    if (s == "adverb")
        return 1;
    if (s == "animal")
        return 2;
    if (s == "body")
        return 3;
    if (s == "clothing")
        return 4;
    if (s == "color")
        return 5;
    if (s == "computer")
        return 6;
    if (s == "conjunction")
        return 7;
    if (s == "container")
        return 8;
    if (s == "emotion")
        return 9;
    if (s == "family")
        return 10;
    if (s == "food")
        return 11;
    if (s == "furniture")
        return 12;
    if (s == "game")
        return 13;
    if (s == "health")
        return 14;
    if (s == "interjection")
        return 15;
    if (s == "job")
        return 16;
    if (s == "kitchen")
        return 17;
    if (s == "language")
        return 18;
    if (s == "math")
        return 19;
    if (s == "money")
        return 20;
    if (s == "music")
        return 21;
    if (s == "nature")
        return 22;
    if (s == "noun")
        return 23;
    if (s == "number")
        return 24;
    if (s == "palindrome")
        return 25;
    if (s == "pronoun")
        return 26;
    if (s == "shape")
        return 27;
    if (s == "transportation")
        return 28;
    //if (s == "verb")
        return 29;
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