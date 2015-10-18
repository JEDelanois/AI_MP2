//
//  CSP.h
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#ifndef __AI_MP2__CSP__
#define __AI_MP2__CSP__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



class Category
{
public:
        
private:

};


class DataBase
{
public:
    //loads in all data
    DataBase(string path);
    
    //overloaded assignment[]
    vector<string>& operator[] (const string nString);
    
    string printAll();
    
private:
    vector< vector<string> > data;
    
    // returns hash value of the coresponding
    int hash(string s);
    
};


#endif /* defined(__AI_MP2__CSP__) */
