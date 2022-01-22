#include "menu.h"
// create file
void create_files()
{
  ofstream library_file("library.txt");
  ofstream patrons_file("patrons.txt");
  if (!library_file || !patrons_file)
  {
    cout << "Error" << endl;
  }
}
// end of creating file

// menu
void admin_menu(vector<Item> &library, vector<Member> &patrons)
{
  int choice;
  do
  {
    cout << "\nADMIN MENU";
    cout << "\n1. ADD A NEW ITEM";
    cout << "\n2. ADD A NEW MEMBER";
    cout << "\n3. DISPLAY ALL ITEMS";
    cout << "\n4. DISPLAY ALL MEMBERS";
    cout << "\n5. CHECK OUT AN ITEM";
    cout << "\n6. RETURN AN ITEM";
    cout << "\n7. MAKE A PAYMENT";
    cout << "\n8. DISPLAY REPORT";
    cout << "\n9. EXIT";
    cout << "\nEnter your choice: ";
    cin >> choice;
    cin.ignore();
    while (!cin >> choice)
    {
      cin.clear();
      cout << "\nInvalid input. Try an integer!";
      cin.ignore();
      cin >> choice;
    }
    while (choice < 1 || choice > 9)
    {
      cin.clear();
      cout << "Invalid input. Select 1-8 ";
      cin >> choice;
      cin.ignore();
    }
    cout << endl;
    switch (choice)
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
  } while (choice != 9);
}
bool log_in()
{
  const string password = "password";
  string input;
  cout << "Password: " << endl;
  cin.ignore();
  getline(cin, input);
  while (input != password)
  {
    cin.clear();
    cout << "Invalid! \nEnter Password: " << endl;
    getline(cin, input);
  }
  return true;
}
void menu(vector<Item> &library, vector<Member> &patrons)
{
  int choice = 0;
  cout << "\nWelcome to the Library Management";
  cout << "\n*********************************" << endl;
  cout << "MENU" << endl;
  cout << "1. RETURN AN ITEM" << endl;
  cout << "2. ADMIN MENU" << endl;
  cout << "Enter your choice: " << endl;
  cin >> choice;
  while (choice < 1 || choice > 2)
  {
    cin.clear();
    cout << "Not available. \nEnter your choice" << endl;
    cin >> choice;
    cin.ignore();
  }
  switch (choice)
  {
  case 1:
    item_check_in(library, patrons);
    break;
  case 2:
    if (log_in())
    {
      admin_menu(library, patrons);
    }
    break;
  }
}
