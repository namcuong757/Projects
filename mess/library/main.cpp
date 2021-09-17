#include "menu.h"
#include "data.h"
#include <vector>
using namespace std;
int main()
{
    vector<Item> library;
    vector<Member> patrons;
    
    //library = load_library_file("library.txt");
    //patrons = load_member_file("patrons.txt");

    menu(library, patrons);
    return 0;
}