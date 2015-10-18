//
//  CSP.cpp
//  AI_MP2
//
//  Created by Erik on 10/18/15.
//  Copyright (c) 2015 Erik. All rights reserved.
//

#include "CSP.h"
#include "string.h"

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
	if (s == "verb")
		return 29;

}

{

	solIdx = 0;
	numWords = scan file
	int i = 0;
	idx0 = scan file	//get all indexes for every word here
		idx1 = scan file
		idx2 = scan file
		//add rest of indexes here

		
	for (int i = 0; j < dictionary[category].length(); i++)
	{
			//if not out of words
			word = dictionary[category][i];
			solution[solIdx][idx0 - 1] = word[0];
			solution[solIdx][idx1 - 1] = word[1];
			solution[solIdx][idx2 - 1] = word[2];

	
			
			for (int j = 0; j < dictionary->category.length(); j++) //iterate through each word of specified category
			{
				idx0 = scan file
					idx1 = scan file
					idx2 = scan file
					word = dictionary->category[j];	//get next word from category

				//if letter in solution vector is not the same letter as the word
				if (solution[solIdx][idx0 - 1] != NULL && word[0] != solution[solIdx][idx0 - 1])
					continue; //go through next iteration (next word)
				else if (solution[idx0 - 1] == NULL)
					solution[solIdx][idx0 - 1] = word[0];

				if (solution[solIdx][idx1 - 1] != NULL && word[1] != solution[solIdx][idx1 - 1])
					continue; //go through next iteration (next word)
				else if (solution[idx1 - 1] == NULL)
					solution[solIdx][idx1 - 1] = word[1];

				if (solution[solIdx][idx2 - 1] != NULL && word[2] != solution[solIdx][idx2 - 1])
					continue; //go through next iteration (next word)
				else if (solution[solIdx][idx2 - 1] == NULL)
					solution[solIdx][idx2 - 1] = word[2];

			}
		
			
	}

	if (solIdx == 0)
		solution[0] = "no solution";
	return solution;
}



