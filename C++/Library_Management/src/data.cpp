#include "data.h"
// Checker check existence of item or member
int item_checker(string isbn, vector<Item> library)
{
  for(int i = 0; i < library.size(); ++i)
  {
    if(isbn == library[i].isbn)
    {
      return i;
    }
  }
  return -1;
}
int member_checker(int memberId, vector<Member> patrons)
{
  for(int i = 0; i < patrons.size(); ++i)
  {
    if(memberId == patrons[i].memberId)
    {
      return i;
    }
  }
  return -1;
}
// end of Checker

// Printer to print item or member infos
void items_printer(vector<Item> library)
{
  if(library.empty())
  {
    cout << "No Items Available" << endl;
  }
  else
  {
    for(int i = 0; i < library.size(); ++i)
    {
      cout << endl;
      cout << "Title: "           << library[i].title << endl;
      cout << "Author: "          << library[i].author << endl;
      cout << "Copy Right Date: " << library[i].copyRightDate << endl;
      cout << "ISBN: "            << library[i].isbn << endl;
      cout << "# Of Copies: "     << library[i].numberOfCopies << endl;
      if(library[i].available)
      {
        cout << "Not ready to check out" << endl;
      }
      else
      {
        cout << "Ready to check out" << endl;
      }
    }
  }
}
void members_printer(vector<Member> members)
{
  if(members.empty())
  {
    cout << "No Members Available" << endl;
  }
  else
  {
    for(int i = 0; i < members.size(); ++i)
    {
      cout << endl;
      cout << "Name: "               << members[i].name << endl;
      cout << "ID: "                 <<members[i].memberId << endl;
      cout << "Remaining Balance: $" << members[i].feeOwed << endl;
      cout << "Borrowed Books: "     << members[i].isbn_borrowed_book << endl;
      if(members[i].waitList)
      {
        cout << "Wailisted" << endl;
      }
    }
  }
}
// ended of Printer

// write data into file, treat file as a data base
void library_to_file(vector<Item>& library, string file)
{
  ofstream out_file;
  out_file.open(file, ios::out);
  if(!out_file)
  {
    cout << "No File Found.Try Again" << endl;
  }
  else
  {
    
    for(int i = 0; i < library.size(); ++i)
    {
      library[i].title.erase(remove(library[i].title.begin(), library[i].title.end(), ' '), library[i].title.end());
      library[i].author.erase(remove(library[i].author.begin(), library[i].author.end(), ' '), library[i].author.end());
      out_file << library[i].title << " " << library[i].author << " " << library[i].copyRightDate << " " << library[i].isbn << " " << library[i].numberOfCopies << " " << library[i].waitList << " " << library[i].issueDate << " " << library[i].available << "\n";
    }
  }
  out_file.close();
}
void members_to_file(vector<Member>& patrons, string file)
{
  ofstream out_file;
  out_file.open(file, ios::out);
  if(!out_file)
  {
    cout << "No File Found.Try Again" << endl;
  }
  else
  {
    for(int i = 0; i < patrons.size(); ++i)
    {
      patrons[i].name.erase(remove(patrons[i].name.begin(), patrons[i].name.end(), ' '), patrons[i].name.end());
      out_file << patrons[i].name << " " << patrons[i].memberId << " " << patrons[i].isbn_borrowed_book << " " << patrons[i].feeOwed << " " << patrons[i].waitList << "\n";
    } 
  }
  out_file.close();
}
// end of writer

