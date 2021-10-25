#include "option.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <locale>
#include <iostream>

using namespace std;
string usage(const char* name)
{
	string text = "Usage: ";
	return text.append(name).append("[-h] [-c] [-p # piles] [-s # stones]\n");
}
string help (const char* name)
{
	string msg = usage(name);
	const string text ="Options:\n-h   Show this text\n-c   Set player two as the computer.\n-p   Manual initial amount of piles in the game.\n-s   Manually initial amount of stones in each pile\nMax: 99, Min:1 for piles and stones";
	return msg.append(text);
}
option get_option(int argc, char** argv)
{
	option options;
	for (int i=1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-h") == 0) {
			cout << help(*argv);
			options.valid = false;
			break;
		} else if (strcmp(argv[i], "-c") == 0) {
			options.has_ai = true;
			options.valid = true;
		} else if (strcmp(argv[i], "-p") == 0) {
			++i;
			options.piles = atoi(argv[i]);
		} else if (strcmp(argv[i], "-s") == 0) {
			++i;
			options.stones = atoi(argv[i]);
		} else {
			cout << "Unknown command received!";
			options.valid = false;
			break;
		}
	}
	return options;
}

