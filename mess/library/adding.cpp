#include <iostream>
#include <string>

#include "adding.h"
// adding new Item or Member
void add_new_item(vector<Item>& library)
{
  Item addingItem;
  string x,n1,n2,n3;
  cout << "** Adding New Item **" << endl;
  cout << "Item Title: " << endl;
  getline(cin, addingItem.title);
  cout << "Item Author: " << endl;
  getline(cin, addingItem.author);
  cout << "Item Copy Right Date: " << endl;
  getline(cin, addingItem.copyRightDate);
  cout << "First Integer of ISBN" << endl;
  cin >> n1;
  cout << "Second Integer of ISBN" << endl;
  cin >> n2;
  cout << "Last Integer of ISBN" << endl;
  cin >> n3;
  cout << "A digit or Letter" << endl;
  cin >> x;
  addingItem.isbn = n1+n2+n3+x;
  cout << "Total copies of Item: " << endl;
  cin >> addingItem.numberOfCopies;
  while(!cin || addingItem.numberOfCopies < 0)
  {
    cin.clear();
    cout << "Wrong Input. Try a number" << endl;
    cin.ignore();
    cin >> addingItem.numberOfCopies;
  }
  library.push_back(addingItem);
  library_to_file(library, "library.txt");
}
void add_new_member(vector<Member>& patrons)
{
  Member newMember;
  cout << "** Adding New Member **" << endl;
  cout << "Member Name: " << endl;
  getline(cin,newMember.name);
  newMember.memberId = patrons.size() + 1;
  newMember.isbn_borrowed_book = "none";
  newMember.feeOwed = 0;
  patrons.push_back(newMember);
  members_to_file(patrons, "patrons.txt");
}
// end of adding