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

/*
 This overloaded operator assumes that each category only appears once in each problem statement
 
 */

CategoryDef&  Parameters::operator[] (const string nString)
{
    int i;
    for( i = 0; i < ctgrs.size(); i++)
    {
        if(ctgrs[i].ctgyName == nString)
            return ctgrs[i];
    }
    // this will cause a seg fault in the event there is no matching category
    return ctgrs[i];
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


vector<string> Parameters::retCategory(int idx)
{
    vector<string> temp;
    //return proper category name
    for(int i = 0; i < ctgrs.size(); i++)
    {
        //check all indexes of the category
        if(idx == ctgrs[i].idxs[0])
            temp.push_back(ctgrs[i].ctgyName);
        
        else if(idx == ctgrs[i].idxs[1])
            temp.push_back(ctgrs[i].ctgyName);
        
        else if(idx == ctgrs[i].idxs[2])
            temp.push_back(ctgrs[i].ctgyName);
    }
    
    //else return empty string
    return temp;
}


int Parameters::retCategoryIndex(int idx)
{
    //return proper category name
    for(int i = 0; i < ctgrs.size(); i++)
    {
        //check all indexes of the category
        if(idx == ctgrs[i].idxs[0])
            return 0;
        
        else if(idx == ctgrs[i].idxs[1])
            return 1;
        
        else if(idx == ctgrs[i].idxs[2])
            return 2;
    }
    
    //else return empty string
    return -1;
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
    cout << endl << endl;
    
    wordsearch(s,-1);
}

//This function does the word search and prints the word trace
//inputs: current solution array and the category index to search
//outpus: none
void CSTworld::wordsearch(string currS,int ctgryIndx)
{
    //error check
    
    if (ctgryIndx + 1 >= parameters.ctgrs.size() )
    {
        string tabs = "";
        
        //get number of tabs needed
        for(int a = 0; a < ctgryIndx + 2; a++)
            tabs += "\t";
        
        cout << "(found result: " << currS << ")" << endl << tabs;
        return;
    }
    
    
    //root check
    if(ctgryIndx == -1 )
        cout << "root" ;


    
    
    int flag = 1;
    //try to fit in words of next category
        // current list of words in category
    vector<string> * curList = &parameters.data[parameters.ctgrs[ctgryIndx+1].ctgyName];
    int i;
    for( i = 0; i < curList->size(); i++)
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
        cout << " -> " << (*curList)[i] << "\t" ;
        wordsearch(temp, ctgryIndx +1);
        
    }
    
    if(flag == 1)
    {
        string tabs = "";
        
        //get number of tabs needed
        for(int a = 0; a < ctgryIndx + 2; a++)
            tabs += "\t";
        
        cout << "BackTrack" << endl << tabs ;
    }
    
}

void CSTworld::LetterSearch()
{
    //make a string of the solution lenght and set tonull
    string s = "";
    s.resize(parameters.solLength);
    for(int i = 0 ; i < parameters.solLength; i++)
        s[i] = ' ';
    
    cout << "Search Order: index order of the letters in the result array" << endl << endl;
    
    lettersearch(s, -1);
}






/*
 Possibly try doing this in a loop fashion instread of a recursion fassion
 
 will need the getCategory funtion to return a list of categories instread of a single category to make sure all categories match
 
 */


void CSTworld::lettersearch(string currS, int idx)
{
    
    //root check
    if(idx == -1 )
    {
        cout << "root" ;
        //call for first letter
        lettersearch(currS, idx +1);
    }
    
    if(idx >= currS.size())
    {
        string tabs = "";
        
        //get number of tabs needed
        for(int a = 0; a < idx + 2; a++)
            tabs += "\t";
        
        cout << "(found result: " << currS << ")" << endl << tabs;
        return;
    }

    
    //get vector of all categories that shar that intex
    vector<string> cats = parameters.retCategory(idx);
    string asdf = cats[0];
    int matches =0;
    // for letters possible for that index
    for(char chr = 'A'; chr <= 'Z'; chr++)
    {
        currS[idx] = chr;
        int flag = 0;
        //for all categories associated with this index
        for(int a = 0; a < cats.size(); a++)
        {
            
            //get the associated list of words
            vector<string> * curList = &parameters.data[ cats[a] ];
            
            //for all words in the list
            for(int i = 0; i < curList->size(); i++)
            {
                //make sure all spaces are either matching or blank
                char z = currS[parameters[cats[a]].idxs[0]];
                char b = (*curList)[i][0];
                string temp1 =(*curList)[i];
                if( ((currS[parameters[cats[a]].idxs[0]] == (*curList)[i][0]) || (currS[parameters[cats[a]].idxs[0]] == ' ') ) &&
                    ((currS[parameters[cats[a]].idxs[1]] == (*curList)[i][1]) || (currS[parameters[cats[a]].idxs[1]] == ' ') ) &&
                    ((currS[parameters[cats[a]].idxs[2]] == (*curList)[i][2]) || (currS[parameters[cats[a]].idxs[2]] == ' ') ) )
                {
                    if(flag == 0)
                    {
                        matches++;
                        flag = 1;
                    }
                }
                //else letter doesnt fit so move on to next possible word or letter
            }
        }
        
        if(matches == cats.size())// if there is atleas one match in every category then pass it on
        {
            //call for next iteration
            lettersearch(currS, idx + 1);
        }
        
        
    }
    
}

















