#include "menu.h"
#include <vector>
#include "data.h"
using namespace std;
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
int main()
{
    vector<Item> library;
    vector<Member> patrons;
    
    library = load_library_file("library.txt");
    patrons = load_member_file("patrons.txt");

    menu(library, patrons);
    return 0;
}