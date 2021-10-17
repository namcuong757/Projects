#include <iostream>
#include "library.h"
using namespace std;

// port
void print_report(vector<Item>& library, vector<Member>& patrons)
{
  cout << "** REPORT **" << endl;
  cout << "------------" << endl;
  cout << endl;
  cout << "Users owed fee" << endl;
  for (int i = 0; i < patrons.size(); ++i)
  {
    if(patrons[i].feeOwed > 0)
    {
      cout << patrons[i].name << " ";
      cout << patrons[i].memberId;
      cout << endl;
    }
  }
  cout << "***" << endl;
  cout << "Items On The Waitlist:" << endl;
  for (int i = 0; i < library.size(); ++i)
  {
    if(library[i].waitList == true)
    {
      cout << library[i].title << " ";
      cout << library[i].isbn;
      cout << endl;
    }
  }
  cout << "***" << endl;
  cout << "Members On The Waitlist:" << endl;
  for (int i = 0; i < patrons.size(); ++i)
  {
    if(patrons[i].waitList == true)
    {
      cout << patrons[i].name << " ";
      cout << patrons[i].memberId;
      cout << endl;
    }
  }
}
// end of report

// pay
void fee_pay(vector<Item>& library, vector<Member>& patrons)
{
  int member_id, member_position, payment;
  char answer;
  cout << "**Payment Terminal**" << endl;
  cout << "--------------------" << endl;
  cout << endl;
  cout << "Please enter you id number" << endl;
  cin >> member_id;
  while(!cin || member_id < 0)
  {
    cin.clear();
    cout << "Wrong Input. Try again" << endl;
    cin.ignore();
    cin >> member_id;
  }
  member_position = member_checker(member_id, patrons);
  if(member_position != -1)
  {
    cout << "Hello " << patrons[member_position].name << "!" << endl;
    cout << "You are owned " << patrons[member_position].feeOwed << endl;
    if(patrons[member_position].feeOwed > 0)
    {
      cout << "Would you like to pay?" << endl;
      cout << "Enter [Y/N]" << endl;
      cin >> answer;
      while(!cin >> answer)
      {
        cin.clear();
        cout << "Wrong input ony enter Y or N" << endl;
        cin.ignore();
        cin >> answer;
      }
      if(toupper(answer) == 'Y')
      {
        cout << "How much would you like to pay" << endl;
        cin >> payment;
        while(!cin || payment < 0)
        {
          cin.clear();
          cout << "Wrong Input. Try again" << endl;
          cin.ignore();
          cin >> payment;
        }
        patrons[member_position].feeOwed = patrons[member_position].feeOwed - payment;
        cout << "Succesfully!" << endl;
        cout << "You are owned " << patrons[member_position].feeOwed;
      }
      else
      {
        cout << "Okay. Have a good day(you might have enter wrong input)" << endl;
      }
    }
    else
    {
      cout << "You are not owned any money" << endl;
    }
  } 
  else
  {
    cout << "You are not a member!" << endl;
  }
  library_to_file(library, "library.txt");
  members_to_file(patrons, "patrons.txt");
}
// end of pay

// load data back into item and member 
vector<Item> load_library_file(string file)
{
  vector<Item> loaded_library;
  Item item;
  ifstream fin;
  fin.open(file);
  if (!fin)
  {
      cerr << "Error in opening the file" << endl;
      return loaded_library; 
  }
  while(fin >> item.title >> item.author >> item.copyRightDate >>  item.isbn >> item.numberOfCopies >> item.waitList >> item.issueDate >> item.available)
  {
      loaded_library.push_back(item);
  }
    return loaded_library;
}
vector<Member> load_member_file(string file)
{
  vector<Member> loaded_members;
  Member member;
  ifstream fin;
  fin.open(file);
  if (!fin)
  {
      cerr << "Error in opening the file" << endl;
      return loaded_members; 
  }
  while(fin >> member.name >> member.memberId >> member.isbn_borrowed_book >> member.feeOwed >> member.waitList)
  {
      loaded_members.push_back(member);
  }
  return loaded_members;
}
// end of loading data