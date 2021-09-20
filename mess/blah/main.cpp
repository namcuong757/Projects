#include <string>
#include <iostream>
using namespace std;

int main()
{
	string in, out;
	cout << "Enter string: ";
	getline(cin, in);
	for(int i = in.length(); i >= 0; --i)
	{
		out += in[i];
	}
	cout << out;
}
