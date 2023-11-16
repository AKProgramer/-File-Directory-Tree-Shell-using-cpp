#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<sstream>
#include <locale>
#include <codecvt>
#include<queue>
#include<filesystem>
using namespace std;
void createADirectry(wstring path)
{
	if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		wcout << L"Directory created successfully!" << endl;
	}
	else {
		cerr << "Error creating directory!" << endl;
	}
}
void createAFile(string path)
{
	ofstream fout;
	fout.open(path);
	if (fout.is_open())
	{
		cout << "File has created successfuly" << endl;
	}
	else
	{
		cout << "Error in File Creating" << endl;
	}
}
void deleteAFile(string location)
{
	if (remove(location.c_str())) {
		cout << "File deleted successfully!" <<endl;
	}
	else {
		cerr << "Error deleting the file " <<endl;
	}
}
void deleteADirectry(wstring location)
{
	if (RemoveDirectory(location.c_str())) {
		cout << "Directory deleted successfully!" << endl;
	}
	else {
		cerr << "Error deleting the directory " << endl;
	}
}
class Directry
{
public:
	string name;
	wstring path;
	wstring location;
	bool type;
public:
	Directry()
	{
		name = "";
		// 0 for directry and 1 for file
		type = false;
	}
	Directry(string n, wstring p, bool t)
	{
		name = n;
		path = p;
		type = t;
		setLocation(path);
	}
	void setPath(wstring p)
	{
		path = p;
		setLocation(p);
	}
	wstring getPath()
	{
		return path;
	}
	void display()
	{
		cout <<"Name : "<< name << endl;
		wcout <<"Path : "<< path << endl;
		if (!type)
		{
			cout << "file type : directry" << endl;
		}
		else 
		{
			cout << "file type : file" << endl;

		}

	}
	wstring getLocation()
	{
		return location;
	}
	string getName()
	{
		return name;
	}
	bool getType()
	{
		return type;
	}
private:
	void setLocation(wstring path)
	{
		locale loc;
		wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		// Convert string to wstring
		wstring wstr = converter.from_bytes(name);
		wstring join = L"\\";
		location = path + join + wstr;
	}

};
struct Node {
	Directry* dir;
	Node* left;
	Node* right;
	Node(Directry* dir)
	{
		this->dir = dir;
		left = NULL;
		right = NULL;
		if (dir->getType() == 0)
		{
			createADirectry(dir->getLocation());
		}
		else 
		{
			locale loc;
			wstring_convert<std::codecvt_utf8<wchar_t>> converter;

			// Convert wstring to string
			string path = converter.to_bytes(dir->getLocation());
			createAFile(path);
		}
	}
};
class FileDirectryTreeShell
{
private:
	Node* head;
public:
	FileDirectryTreeShell()
	{
		head = NULL;
	}
	Node* get()
	{
		return head;
	}
	FileDirectryTreeShell(Directry* dir)
	{
		head = new Node(dir);
	}
	bool searching(Node* root, wstring path)
	{
		if (root == NULL)
		{
			return 0;
		}
		else if (root->dir->getLocation() == path)
		{
			return 1;
		}
		
		bool left=searching(root->left, path);
		bool right=searching(root->right, path);
		if (left || right)
		{
			return 1;
		}
		return 0;
	}
	void levelOrderTraversal()
	{
		queue<Node*> queue;
		queue.push(head);
		while (!queue.empty())
		{
			Node* temp=queue.front();
			queue.pop();
			temp->dir->display();
			if (temp->left != NULL)
			{
				queue.push(temp->left);
			}
			if (temp->right != NULL)
			{
				queue.push(temp->right);
			}

		}
	}
	void trackingFileDirectryRecord(Directry* dir)
	{
		if (head == NULL)
		{
			head = new Node(dir);
			return;
		}
	else if (head->left == NULL)
		{
		
			head->left = new Node(dir);
			return;
		}
	else if (head->right == NULL)
		{
			head->right = new Node(dir);
			return;
		}
	else 
		{
			locale loc;
			wstring_convert<std::codecvt_utf8<wchar_t>> converter;

			// Convert wstring to string
			string path = converter.to_bytes(dir->getPath());
			string temp = path;
			string find="";
			// getting the directry where dir has to place
			//last directry in path string is the directry where i have to insert dir
			stringstream sstr(temp);
			while (getline(sstr, temp, '\\'))
			{
				
				find = temp;
			}
			bool check = false;
				check = searching(head, dir->getPath());
			if (check)
			{
				insertion(head,dir, find);
			}
			else
			{
				cout << "	EXCEPTION : file or directry can't be create double check your path and try again" << endl;
			}
			
		}
		
	}
	void deletion(Node* root, wstring location, bool type)
	{
		if (searching(root, location))
		{
			makeDeletion(root, location, type);
		}
		else
		{
			cout << "ERROR : file or directry not found!" << endl;
		}
	}
private:
	void makeDeletion(Node* root, wstring locat, bool type)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->dir->getLocation() == locat)
		{
			if (root->left == NULL && root->right == NULL)
			{
				if (type == 0)
				{
					deleteADirectry(locat);
				}
				else
				{
					locale loc;
					wstring_convert<std::codecvt_utf8<wchar_t>> converter;

					// Convert wstring to string
					string location = converter.to_bytes(locat);
					deleteAFile(location);
				}
					
				delete root;
			}
			else
			{
				int input;
				cout << "WARNING : there is some data in this specific location\ndo you want to delete? \npress 1 to delete or press 0 if you don't want to delete." << endl;
				cin >> input;
				if (input)
				{
					if (type == 0)
						deleteADirectry(locat);
					else
					{
						locale loc;
						wstring_convert<std::codecvt_utf8<wchar_t>> converter;

						// Convert wstring to string
						string location = converter.to_bytes(locat);
						deleteAFile(location);
					}
						
					delete root;
				}
			}
		}
		makeDeletion(root->left, locat, type);
		makeDeletion(root->right, locat, type);
	}
	void insertion(Node* &root,Directry* dir, string name)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->dir->getName() == name)
		{
			if (dir->getType() == 1)
			{
				if (root->right != NULL)
				{
					root->right = new Node(dir);
				}
				else
				{
					cout << "EXCEPTION : file can't create here because give path already have a file" << endl;
				}

			}
			else
			{
				if (root->left != NULL)
				{
					Node* temp = root->left;
					root->left = new Node(dir);
					root->left->left = temp;
				}
				else 
				{
					root->left = new Node(dir);
				}
			}

		}
		insertion(root->left,dir, name);
		insertion(root->right,dir, name);
	}
};