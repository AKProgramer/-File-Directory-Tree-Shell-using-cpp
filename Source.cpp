#include <iostream>
#include"Header.h"
#include <Windows.h>
#include<string>
using namespace std;
int main() {
    int choice;
    wstring str;
    wstring sourceLocation;
    wstring distLocation;
    bool type = 0;
    FileDirectryTreeShell root;
     while (1)
    {
        Directry* dir = new Directry;
        cout << "Press 1 to create a Directry\n NOTE : press 1 for file press 0 for directry" << endl;
        cout << "Press 2 to delete a Directry" << endl;
        cout << "Press 3 to delete a file" << endl;
        cout<<"Press 4 to copy a file " << endl;
        cout << "Press 5 to move a file" << endl;
       
        cout << "Press 6 for merging two directries" << endl;
        cout << "Press 7 to search a file" << endl;
        cout << "Press 8 to search a folder" << endl;
        cout << "Press 9 for level order traversal" << endl;
        cout << "Press 10 to exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            string name;
            wstring path;
            bool type;
            cin.ignore();
            cout << "Enter name : ";
            getline(cin, name);
            dir->setName(name);
           
            cout << "Enter path : ";
            getline(wcin, path);
            dir->setPath(path);
           
            cout << "Enter type : ";
            cin >> type;
            dir->setType(type);
            root.trackingFileDirectryRecord(dir);
        }
        else if (choice == 2)
        {
            cin.ignore();
            wstring location;
            cout << "Enter directry location you want to delete" << endl;
            getline(wcin, location);
            root.deleteADirectry(location);
        }
        else if (choice == 3)
        {
            cin.ignore();
            string fileName;
            cout << "Enter file name" << endl;
            getline(cin, fileName);
            root.deleteAFile(fileName);
        }
        else if (choice == 4)
        {
            cin.ignore();
            string fileName;
            wstring destination;
            cout << "Enter file name" << endl;
            getline(cin, fileName);
            cout << "Enter distination directry full path" << endl;
            getline(wcin, destination);

            root.copyAFile(fileName, destination);

        }
        else if (choice == 5)
        {
            cin.ignore();
            string fileName;
            wstring destination;
            cout << "Enter file name" << endl;
            getline(cin, fileName);
            cout << "Enter distination directry location" << endl;
            getline(wcin, destination);
            root.moveAFile(fileName, destination);
        }
        else if (choice == 6)
        {
            cin.ignore();
            wstring source, distination;
            string rename;
            cout << "Enter source location" << endl;
            getline(wcin, source);
            cout << "Enter distination directry location" << endl;
            getline(wcin, distination);
            cout << "Enter new name of distination directry" << endl;
            getline(cin, rename);
            root.mergeDirectries(source, distination, rename);
        }
        else if (choice == 7)
        {
            cin.ignore();
            string name;
            cout << "Enter file name" << endl;
            getline(cin, name);
            if (!root.printFilePath(root.get(), name))
            {
                cout << "ERROR : file does not exists" << endl;
            }
        }
        else if (choice == 8)
        {
            cin.ignore();
            wstring location;
            cout << "Enter location of directry : ";
            getline(wcin, location);
           cout<<root.searchADirectry(root.get(), location) << endl;
        }
        else if (choice == 9)
        {
            cin.ignore();
            root.levelOrderTraversal();
        }
        else
        {
            break;
        }
    }
    
    return 0;
}