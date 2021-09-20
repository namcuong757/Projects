#include "menu.h"
// create file
void create_files()
{
  ofstream library_file("library.txt");
  ofstream patrons_file("patrons.txt");
  if(!library_file || ! patrons_file)
  {
    cout << "Error" << endl;
  }
}
// end of creating file

// menu
void menu(vector<Item>& library, vector<Member>& patrons)
{
  int choice;
  do
  {
    cout << "\nWelcome to the Library Management";
    cout << "\n*********************************" << endl;
    cout << "\nMenu";
    cout << "\n1. Add an Item";
    cout << "\n2. Add an Member";
    cout << "\n3. Print all Items";
    cout << "\n4. Print all Members";
    cout << "\n5. Check Out an Item";
    cout << "\n6. Return an Item";
    cout << "\n7. Payment Terminal";
    cout << "\n8. Print Report";
    cout << "\n9. Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;
    cin.ignore();
    while(!cin >> choice)
    {
      cin.clear();
      cout << "\nInvalid input. Try an integer!";
      cin.ignore();
      cin >> choice;
    } 
    while(choice < 1 || choice > 9)
    {   
      cin.clear();
      cout << "Invalid input. Select 1-8 ";
      cin >> choice;
      cin.ignore();
    }
    cout << endl; 
    switch(choice)
    { 
      case 1:
        add_new_item(library);
        break;
      case 2:
        add_new_member(patrons);
        break;
      case 3:
        items_printer(library);
        break;
      case 4:
        members_printer(patrons);
        break;
      case 5:
        item_check_out(library, patrons);
        break;
      case 6:
        item_check_in(library, patrons);
        break;
      case 7:
        fee_pay(library, patrons);
        break;
      case 8:
        print_report(library, patrons);
        break;
    }
  }while(choice != 9);
}
