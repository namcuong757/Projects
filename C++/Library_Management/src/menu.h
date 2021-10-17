#ifndef MESS_MENU_H
#define MESS_MENU_H

#include <vector>
#include <iostream>
#include "data.h"
#include "library.h"
#include "adding.h"
#include "checkOutnIn.h"
using namespace std;

void create_files();
void menu(vector<Item>& library, vector<Member>& patrons);

#endif
