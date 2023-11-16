#include <iostream>
#include"Header.h"
#include <Windows.h>
#include<string>
using namespace std;
int main() {
    int choice;
    wstring str;
    wstring location;
    bool type = 0;
    FileDirectryTreeShell root;
     while (1)
    {
        Directry* dir = new Directry;
        cout << "Press 1 to create a Directry" << endl;
        cout << "Press 2 for level order traversal" << endl;
        cout << "Press 3 to delete a directry" << endl;
        cout << "Press 4 to exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter name : ";
            cin >> dir->name;
            cout << "Enter path : ";
            wcin.ignore();
            getline(wcin, str);
            dir->setPath(str);
            cout << "Enter type : ";
            cin >> dir->type;

            root.trackingFileDirectryRecord(dir);
        }
        else if (choice == 2)
        {
            root.levelOrderTraversal();
        }
        else if (choice == 3)
        {
            cout << "Enter path : ";
            wcin >> location;
            cout << "Press 1 if it is a file or 0 if it is a directry" << endl;
            cin >> type;
            root.deletion(root.get(),location, type);
        }
        else if (choice == 4)
        {
            break;
        }
    }
    return 0;
}