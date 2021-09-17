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

// Checker check existence of item or member
int item_Checker(string isbn, vector<Item> library)
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
int member_Checker(int memberId, vector<Member> patrons)
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
void itemsPrinter(vector<Item> library)
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
			cout << library[i].title << endl;
			cout << library[i].author << endl;
			cout << library[i].copyRightDate << endl;
			cout << library[i].isbn << endl;
			cout << library[i].numberOfCopies << endl;
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
void membersPrinter(vector<Member> members)
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
			cout << members[i].name << endl;
			cout << members[i].memberId << endl;
			cout << "$" << members[i].feeOwed << endl;
			cout << members[i].isbn_borrowed_book << endl;
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

// adding new Item or Member
void addNewItem(vector<Item>& library)
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
void addNewMember(vector<Member>& patrons)
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
	member_position = member_Checker(id_temp, patrons);
	if(member_position != -1)
	{
		if(patrons[member_position].feeOwed == 0.0)
		{
			if(patrons[member_position].isbn_borrowed_book == "none")
			{
				cout << "Hello " << patrons[member_position].name << "!" << endl;
				cout << "Enter IBSN of item you want to check out" << endl;
				getline(cin, isbn_temp);
				item_position = item_Checker(isbn_temp, library);
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
	member_position = member_Checker(id_temp, patrons);
	if(member_position != -1)
	{
		if(patrons[member_position].isbn_borrowed_book != "none")
		{
			item_position = item_Checker(patrons[member_position].isbn_borrowed_book, library);
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

// Report
void printReport(vector<Item>& library, vector<Member>& patrons)
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
	member_position = member_Checker(member_id, patrons);
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
				addNewItem(library);
				break;
			case 2:
				addNewMember(patrons);
				break;
			case 3:
				itemsPrinter(library);
				break;
			case 4:
				membersPrinter(patrons);
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
				printReport(library, patrons);
				break;
		}
	}while(choice != 9);
}
// end of menu

void library()
{
	create_files();
	vector<Item> library = load_library_file("library.txt");
	vector<Member> patrons = load_member_file("patrons.txt");
	menu(library, patrons);
}
// driver
int main()
{
	library();
	return 0;
}
