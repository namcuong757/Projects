#ifndef MESS_CHECKOUTNIN_H
#define MESS_CHECKOUTNIN_H
#include <vector>
#include "data.h"
using namespace std;

void item_check_out(vector<Item>& library, vector<Member>& patrons);
void item_check_in(vector<Item>& library, vector<Member>& patrons);
#endif
