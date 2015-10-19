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
    Init(path);
}

void DataBase::Init(string path)
{
    string temp;
   
    //clear all stuff incase of a reassignment
    CatNames.resize(0);
    data.resize(0);
   
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

void CategoryDef::print()
{
    cout <<  "Category: " << ctgyName << " " << idxs[0] << " " << idxs[1] << " " << idxs[2] << endl;
}

Parameters::Parameters(string probpath, string datapath)
{
    Init(probpath, datapath);
}
void Parameters::Init(string probpath, string datapath)
{
    //assign all data and reset what might have already been there
    data.Init(datapath);
    ifstream infile;
    infile.open(probpath);
    ctgrs.resize(0);
    
    if(!infile.eof())
    {
        //get length of the solution
        infile >> solLength;
        
        while(!infile.eof())
        {
            
            string temp;
            int itemp;
            
            infile >> temp;
            if(temp == "")
                break;
            temp.pop_back();
            
            //make new node
            ctgrs.push_back(CategoryDef());
            
            ctgrs[ctgrs.size() -1 ].ctgyName = temp;
            
            infile >> itemp;
            ctgrs[ctgrs.size() -1 ].idxs[0] = itemp-1;
            
            infile >> temp;
            
            infile >> itemp;
            ctgrs[ctgrs.size() -1 ].idxs[1] = itemp-1;
            
            infile >> temp;
            
            infile >> itemp;
            ctgrs[ctgrs.size() -1 ].idxs[2] = itemp-1;
            
            
            
        }
        
        infile.close();
    
    }
    
    
}

void Parameters::print()
{
    cout << "Here is the list of Parameters" << endl;
    for(int i = 0; i < ctgrs.size(); i++)
    {
        ctgrs[i].print();
    }
    cout << endl;
}


CSTworld::CSTworld(string probpath, string datapath)
{
    parameters.Init(probpath,datapath);
}


void CSTworld::WordSearch()
{
    //make a string of the solution lenght and set tonull
    string s = "";
    s.resize(parameters.solLength);
    for(int i = 0 ; i < parameters.solLength; i++)
        s[i] = ' ';
    
    cout << "Search Order: ";
    for(int i = 0; i < parameters.ctgrs.size(); i++)
    {
        cout << parameters.ctgrs[i].ctgyName;
        if(i < parameters.ctgrs.size() -1)
            cout << "->";
    }
    cout << endl;
    
    wordsearch(s,-1);
}

void CSTworld::wordsearch(string currS,int ctgryIndx)
{
    //error check
    
    if (ctgryIndx + 1 >= parameters.ctgrs.size() )
    {
        cout << "(found result: " << currS << ")" << endl;
        return;
    }
    
    
    //root check
    if(ctgryIndx == -1 )
        cout << "root" ;

    string tabs = "";
    //get number of tabs needed
    for(int a = 0; a < ctgryIndx + 2; a++)
        tabs += "\t";
    
    
    int flag = 1;
    //try to fit in words of next category
        // current list of words in category
    vector<string> * curList = &parameters.data[parameters.ctgrs[ctgryIndx+1].ctgyName];
    for(int i = 0; i < curList->size(); i++)
    {
        //copy over string to pass along
        string temp(currS);

        //if the character is null fill it in
        if(temp[parameters.ctgrs[ctgryIndx +1].idxs[0]] == ' ' )
        {
            int as =parameters.ctgrs[ctgryIndx +1].idxs[0];
            //place coresponding character in
            temp[as] = (*curList)[i][0];
        }
        //there is a character present so if its not the same then continue
        else if(temp[parameters.ctgrs[ctgryIndx +1].idxs[0]] != (*curList)[i][0])
        {
            continue;
        }
        
        //if the character is null fill it in
        if(temp[parameters.ctgrs[ctgryIndx +1].idxs[1]] == ' ' )
        {
            //place coresponding character in
            temp[parameters.ctgrs[ctgryIndx +1].idxs[1]] = (*curList)[i][1];
        }
        //there is a character present so if its not the same then continue
        else if(temp[parameters.ctgrs[ctgryIndx +1].idxs[1]] != (*curList)[i][1])
        {
            continue;
        }

        
        //if the character is null fill it in
        if(temp[parameters.ctgrs[ctgryIndx +1].idxs[2]] == ' ' )
        {
            //place coresponding character in
            temp[parameters.ctgrs[ctgryIndx +1].idxs[2]] = (*curList)[i][2];
        }
        //there is a character present so if its not the same then continue
        else if(temp[parameters.ctgrs[ctgryIndx +1].idxs[2]] != (*curList)[i][2])
        {
            continue;
        }
        
        
        //if code gets here then next word is succesfully placed in here so call on current word
        flag = 0;
        cout<<endl << tabs << "-> " << (*curList)[i] << "\t" ;
        wordsearch(temp, ctgryIndx +1);
        
    }
    
    if(flag == 1)
        cout << "BackTrack";
    
}





