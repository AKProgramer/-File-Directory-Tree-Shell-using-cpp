#include <iostream>
#include"Header.h"
#include <Windows.h>
#include<string>
using namespace std;
int main() {
    FileDirectryTreeShell root;
    Directry* dir1=new Directry;
    dir1->name = "root";
    dir1->setPath(L"D:\\Fast University\\Programming\\Assignment_3");
    dir1->type = 0;

    Directry* dir2=new Directry;
    dir2->name = "PatientsData";
    dir2->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root");
    dir2->type = 0;
    Directry* dir3=new Directry;
    dir3->name = "Log";
    dir3->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root");
    dir3->type = 0;

    Directry* dir4=new Directry;
    dir4->name = "PatientsHome";
    dir4->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root\\PatientsData");
    dir4->type = 0;
    Directry* dir5=new Directry;
    dir5->name = "PatientsList.txt";
    dir5->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root\\PatientsData");
    dir5->type = 1;

    Directry* dir6=new Directry;
    dir6->name = "LogsHome";
    dir6->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root\\Log");
    dir6->type = 0;

    Directry* dir7=new Directry;
    dir7->name = "LogReport.txt";
    dir7->setPath( L"D:\\Fast University\\Programming\\Assignment_3\\root\\Log");
    dir7->type = 1;

    Directry* dir8=new Directry;
    dir8->name = "PatientA";
    dir8->setPath(L"D:\\Fast University\\Programming\\Assignment_3\\root\\PatientsData\\PatientsHome");
    dir8->type = 0;

    root.trackingFileDirectryRecord(dir1);
    root.trackingFileDirectryRecord(dir2);
    root.trackingFileDirectryRecord(dir3);
    root.trackingFileDirectryRecord(dir4);
    root.trackingFileDirectryRecord(dir5);
    root.trackingFileDirectryRecord(dir6);
    root.trackingFileDirectryRecord(dir7);
    root.trackingFileDirectryRecord(dir8);
    wstring sourceLocation=L"D:\\Fast University\\Programming\\Assignment_3\\root\\PatientsData\\PatientsHome";
    wstring distLocation=L"D:\\Fast University\\Programming\\Assignment_3\\root\\Log";
   root.levelOrderTraversal();
   cout << endl;
    root.moveAFile("LogRepot.txt", sourceLocation);
    cout << endl;
   root.levelOrderTraversal();
   /*cout << endl;
    root.mergeDirectries(sourceLocation, distLocation,"L");
    root.levelOrderTraversal();*/
    
    /*int choice;
    wstring str;
    wstring sourceLocation;
    wstring distLocation;
    bool type = 0;
    FileDirectryTreeShell root;
     while (1)
    {
        Directry* dir = new Directry;
        cout << "Press 1 to create a Directry" << endl;
        cout << "Press 2 for level order traversal" << endl;
        cout << "Press 3 for merging two directries" << endl;
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

            root.trackingFileDirectryRecord(root.get(),dir);
        }
        else if (choice == 2)
        {
            root.levelOrderTraversal();
        }
        else if (choice == 3)
        {
            cout << "Enter location of source directry : ";
            wcin >> sourceLocation;
            cout << "Enter location of distination directry : ";
            wcin >> distLocation;
            root.mergeTwoDirectries(root.get(), sourceLocation, distLocation);
        }
        else if (choice == 4)
        {
            break;
        }
    }
    return 0;*/
}