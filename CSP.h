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

class DataBase
{
public:
    //loads in all data
    DataBase(){}
    DataBase(string path);
    void Init(string path);

    int size(){return data.size();}
    
    //overloaded assignment[]
    vector<string>& operator[] (const string nString);
    
    string printAll();
    vector<string> CatNames;
    
    
private:
    vector< vector<string> > data;
    
    // returns hash value of the coresponding
    int hash(string s);
    
    
};

class CategoryDef
{
public:
    string ctgyName;
    
    int idxs[3];
    
    void print();
    
private:
    
};


class Parameters
{
public:
    Parameters(){}
    Parameters(string probpath, string datapath);
    void Init(string probpath, string datapath);
    
    DataBase data;
    
    vector<CategoryDef> ctgrs;
    
    void print();
    int solLength;
    
private:
    
};


class CSTworld
{
public:
    CSTworld(string probpath, string datapath);
    Parameters parameters;
    void WordSearch();
    
private:
    void wordsearch(string currS,int ctgryIndx);
    
};


#endif /* defined(__AI_MP2__CSP__) */








