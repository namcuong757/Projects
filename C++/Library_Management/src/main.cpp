#include "menu.h"
#include "data.h"
#include <vector>
using namespace std;
int main()
{
    vector<Item> library;
    vector<Member> patrons;
    items_printer(library);
    library = load_library_file("library.txt");
    patrons = load_member_file("patrons.txt");

    admin_menu(library, patrons);
    return 0;
}
