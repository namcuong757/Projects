#ifndef OPTION_H
#define OPTION_H
#include <cstdint>
#include <string>
#include <locale>
#include <iostream>
using namespace std;

struct option{
	bool valid = true;
	bool has_ai = false;
	bool set_stones = false;
	bool set_piles = false;
	int piles = 0;
	int stones = 0;
};
string help(const char*);
string usage(const char*);
option get_option(int num, char** argv);

#endif

