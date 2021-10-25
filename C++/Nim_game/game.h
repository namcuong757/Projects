#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>

string get_name(string& prompt, string& input);
bool gameOver(vector<int> piles);
void declareWinner (string whoseTurn);
void gameStatus(vector<int> piles);
void manualPlayer(vector<int> &piles, const string &player);
void playGame(vector<int> piles, const string& player1,const string& player2, bool ai);


#endif
