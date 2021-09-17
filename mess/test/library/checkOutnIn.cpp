#include <iostream>
#include "checkOutnIn.h"

using namespace std;
// Check out and Check In. most importance part of project
void item_check_out(vector<Item>& library, vector<Member>& patrons)
{
  int id_temp , member_position, item_position;
  string isbn_temp;
  cout << "**Checking Out**" << endl;
  cout << "----------------" << endl;
  cout << endl;
  cout << "Enter your member ID" << endl;
  cin >> id_temp;
  while(!cin || id_temp < 0)
  {
    cin.clear();
    cout << "Wrong Input. Try again" << endl;
    cin.ignore();
    cin >> id_temp;
  }
  member_position = member_checker(id_temp, patrons);
  if(member_position != -1)
  {
    if(patrons[member_position].feeOwed == 0.0)
    {
      if(patrons[member_position].isbn_borrowed_book == "none")
      {
        cout << "Hello " << patrons[member_position].name << "!" << endl;
        cout << "Enter IBSN of item you want to check out" << endl;
        getline(cin, isbn_temp);
        item_position = item_checker(isbn_temp, library);
        if(item_position != -1)
        {
          if(library[item_position].available)
          {
            string issueDate;
            cout << "Enter issue date" << endl;
            getline(cin, issueDate);
            library[item_position].issueDate = issueDate;
            library[item_position].available = false;
            patrons[member_position].waitList = false;
            patrons[member_position].isbn_borrowed_book = library[item_position].isbn;
            cout << "Checked out succesfully!" << endl;
            cout << "Please return in next 7 days" << endl;
          }
          else
          {
            cout << "The item is not available" << endl;
            patrons[member_position].waitList = true;
            library[item_position].waitList = true;
            cout << "You are on the wait list for this item" << endl;
          }
        }
        else
        {
          cout << "Item cannot be found" << endl;
        }
      }
      else
      {
        cout << "Please return the item with isbn: " << patrons[member_position].isbn_borrowed_book << "before checking out" << endl;
      }
    }
    else
    {
      cout << "You are owned $" << patrons[member_position].feeOwed << endl;
      cout << "Please pay before checking out" << endl;
    }
  }
  else
  {
    cout << "You are not a member. Please register!" << endl;
  }
  library_to_file(library, "library.txt");
  members_to_file(patrons, "patrons.txt");
}
void item_check_in(vector<Item>& library, vector<Member>& patrons)
{
  int id_temp , member_position, item_position, lateDays;
  string isbn_temp;
  cout << "**Checking In**" << endl;
  cout << "----------------" << endl;
  cout << endl;
  cout << "Enter your member ID" << endl;
  cin >> id_temp;
  while(!cin || id_temp < 0)
  {
    cin.clear();
    cout << "Wrong Input. Try again" << endl;
    cin.ignore();
    cin >> id_temp;
  }
  member_position = member_checker(id_temp, patrons);
  if(member_position != -1)
  {
    if(patrons[member_position].isbn_borrowed_book != "none")
    {
      item_position = item_checker(patrons[member_position].isbn_borrowed_book, library);
      if(item_position != -1)
      {
        cout << "Issue Date: " << library[item_position].issueDate << endl;
        cout << "How many days are they late since the due days [+7 days since the issue days]" << endl;
        cin >> lateDays;
        patrons[member_position].feeOwed = lateDays * 5;
        patrons[member_position].isbn_borrowed_book = "none";
        library[item_position].waitList = false;
        library[item_position].available = true;
        library[item_position].issueDate = "none";
        cout << "Checked In succesfully" << endl;
        cout << "Thank you for using our service" << endl;
      }
      else
      {
        cout << "Cannot found item" << endl;
      }
    }
    else
    {
      cout << "You are not currenly borrowed any items" << endl;
    }
  }
  else
  {
    cout << "You are not a member. Please register!" << endl;
  }
  library_to_file(library, "library.txt");
  members_to_file(patrons, "patrons.txt");
}
// End of check in and out