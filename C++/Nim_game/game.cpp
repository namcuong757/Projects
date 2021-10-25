#include "option.h"
#include <string>
#include <iostrean>
#include <math.h>
#include <vector>

using namespace std;

string get_name(string& prompt, string& input)
{
	while(true)
	{  
		cout << prompt << " ";
		cin >> input;
		if(input.length() <= 0 )
		{
			cin.clear();
			cin.ignore();
			cout << " Please re-enter a valid name" << endl;
		}
		else
		{
			prompt.append(input);
			break;
		}  
	}
	return prompt;	
}

bool gameOver(vector<int> piles)
{
	for(int i = 0; i < piles.size(); i++)
	{
		if(piles[i] !=0){
			return false;
		}
	}
	return true;
}
void declareWinner (string whoseTurn)
{
	if(whoseTurn == "COMPUTER")
	{
		cout << "\nCOMPUTER WON, YOU ARE WEAK\n\n";
	}
	else
	{
		cout << whoseTurn << " WON, NICE\n\n";
	}
	return;
}
void gameStatus(vector<int> piles)
{
	for( int i = 0; i < piles.size(); ++i)
	{
		cout << "\nHeap" << i + 1 << " ["<< piles[i] << "] ";
		for(int j = 0; j < piles[i]; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}
	return;
}
void manualPlayer(vector<int> &piles, const string &player)
{
	struct option opt;
	int heap = opt.piles;
	int stones = opt.stones;
	cout << player << "'s turn\n";
	if(piles.size() > 1)
	{
		cout << "\nWhich heap ? ";
		cin >> heap;
		while(!cin >> heap)
		{
			cin.clear();
			cout << "Invalid input. Try again with an integer";
			cin.ignore();
			cin >> heap;
		}
		while( heap < 0 || heap > piles.size())
		{
			cout << "In valid input. No heap exist\n";
			cout << "Try agin: ";
			cin >> heap;
		}

		heap = heap - 1;
	}
	else
	{
		heap = 0;
	}
	cout << "How many stones would you like to remove ? ";
	cin >> stones;
	while(!cin >> stones)
	{
		cin.clear();
		cout << "Invalid input. Try again with an integer";
		cin.ignore();
		cin >> stones;
	}
	if(piles[heap] >= stones && stones > 0)
	{
		piles[heap] = piles[heap] - stones;
	}
	else
	{cout << "Not enough stones. Try again \n";}
	return;
}
void playGame(vector<int> piles, const string &player1,const string &player2, bool ai)
{
	string turn = player1;
	while(gameOver(piles) == false)
	{
		gameStatus(piles);
		if(ai)
		{
			if(turn == player1)
			{
				manualPlayer(piles, player1);
				turn = player2;
			}
			else
			{
				makeMove(piles);
				turn = player1;
			}
		}
		else
		{
			if(turn == player1)
			{
				manualPlayer(piles, player1);
				turn = player2;
			}
			else
			{
				manualPlayer(piles, player2);
				turn = player1;
			}
		}
		for(int i = 0; i < piles.size(); ++i)
		{
			if(piles[i] == 0){
				piles.erase(piles.begin() + i);
			}
		}
	}

	if(turn == player2)
	{
		declareWinner(player1);
	}
	else
	{
		declareWinner(player2);
	}
	return;
}
