#include "option.h"
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

string get_name(const string &prompt, string &input)
{
	string temp = prompt;
	while (true)
	{
		cout << temp << " ";
		cin >> input;
		if (input.length() <= 0)
		{
			cin.clear();
			cin.ignore();
			cout << " Please re-enter a valid name" << endl;
		}
		else
		{
			temp.append(input);
			break;
		}
	}
	return temp;
}

bool gameOver(vector<int> piles)
{
	for (int i = 0; i < piles.size(); i++)
	{
		if (piles[i] != 0)
		{
			return false;
		}
	}
	return true;
}
void declareWinner(string whoopturn)
{
	if (whoopturn == "COMPUTER")
	{
		cout << "\nCOMPUTER WON, YOU ARE WEAK\n\n";
	}
	else
	{
		cout << whoopturn << " WON, NICE\n\n";
	}
	return;
}
void gameStatus(vector<int> piles)
{
	for (int i = 0; i < piles.size(); ++i)
	{
		cout << "\nHeap" << i + 1 << " [" << piles[i] << "] ";
		for (int j = 0; j < piles[i]; ++j)
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
	cout << endl;
	cout << player << "'s turn\n";
	if (piles.size() > 1)
	{
		cout << "\nWhich heap ? ";
		cin >> heap;
		while (!cin >> heap)
		{
			cin.clear();
			cout << "Invalid input. Try again with an integer";
			cin.ignore();
			cin >> heap;
		}
		while (heap < 0 || heap > piles.size())
		{
			cout << "In valid input. No heap exist\n";
			cout << "Which heap ?  ";
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
	while (!cin >> stones)
	{
		cin.clear();
		cout << "Invalid input. Try again with an integer";
		cin.ignore();
		cin >> stones;
	}
	while (piles[heap] < stones || stones < 0)
	{
		cin.clear();
		cout << "Not enought stones. How many stones? ";
		cin.ignore();
		cin >> stones;
	}
	piles[heap] = piles[heap] - stones;
	return;
}
void makeMove(vector<int> &piles)
{
	bool did_make_move = true;
	int heap = 0;
	int stones = 0;
	cout << "BOT's turn\n";
	while (did_make_move)
	{
		heap = rand() % piles.size();
		stones = rand() % 100;
		if (piles[heap] >= stones && stones > 0)
		{
			piles[heap] = piles[heap] - stones;
			cout << "Bot took " << stones << " stones out of heap " << heap + 1 << endl;
			did_make_move = false;
		}
	}
}
void playGame(vector<int> &piles, const string &player1, const string &player2, bool ai)
{
	string turn = player1;
	while (gameOver(piles) == false)
	{
		gameStatus(piles);
		if (ai)
		{
			if (turn == player1)
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
			if (turn == player1)
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
		for (int i = 0; i < piles.size(); ++i)
		{
			if (piles[i] == 0)
			{
				piles.erase(piles.begin() + i);
			}
		}
	}

	if (turn == player2)
	{
		declareWinner(player1);
	}
	else
	{
		declareWinner(player2);
	}
}
void start_game(int num, char **arv)
{
	string in;
	option opt;
	do
	{
		string player1;
		string player2;
		opt = get_option(num, arv);
		vector<int> piles;
		int stones = opt.stones;
		int pileNum = opt.piles;
		if (opt.valid)
		{
			if (opt.set_piles)
			{
				piles.resize(pileNum);
			}
			if (opt.set_stones)
			{
				for (int i = 0; i < piles.size(); i++)
				{
					piles[i] = stones;
				}
			}
			if (piles.empty())
			{
				int size = rand() % 10 + 1;
				for (int i = 0; i < size; ++i)
				{
					int s = rand() % 10 + 1;
					piles.push_back(s);
				}
			}
			if (opt.has_ai)
			{
				cout << "-Computer play On-" << endl;
				get_name("Player 1 name: ", player1);
				//player2 = "bot";
			}
			else
			{
				get_name("PLAYER 1 NAME: ", player1);
				get_name("PLAYER 2 name: ", player2);
			}
			playGame(piles, player1, player2, opt.has_ai);

			cin.ignore();
			cout << "WOULD YOU LIKE TO PLAY THIS AGAIN ? (Y/N)" << endl;
			getline(cin, in);
			cout << endl;
		}
	} while (toupper(in[0]) == 'Y' || toupper(in[0]) == 'y');
}
