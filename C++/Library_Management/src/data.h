#ifndef MESS_DATA_H
#define MESS_DATA_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;

// struct declare Item and Member
struct Item
{
  string title, author, copyRightDate, isbn;
  string issueDate = "none";
  int numberOfCopies;
  bool waitList = false;
  bool available = true;
  Item(){}
  
};
struct Member
{
  string name;
  int memberId;
  string isbn_borrowed_book;
  int feeOwed;
  bool waitList = false;
  Member(){}
};
// end of struct

int item_checker(string isbn, vector<Item> library);
int member_checker(int memberId, vector<Member> patrons);
void items_printer(vector<Item> library);
void members_printer(vector<Member> members);
void library_to_file(vector<Item>& library, string file);
void members_to_file(vector<Member>& patrons, string file);
vector<Item> load_library_file(string file);
vector<Member> load_member_file(string file);
#endif
