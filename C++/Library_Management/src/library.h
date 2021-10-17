#ifndef MESS_LIBRARY_H
#define MESS_LIBRARY_H
#include <vector>
#include "data.h"
using namespace std;

void print_report(vector<Item>& library, vector<Member>& patrons);
void fee_pay(vector<Item>& library, vector<Member>& patrons);
#endif
