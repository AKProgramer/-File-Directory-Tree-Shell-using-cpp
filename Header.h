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
	void setName(string name)
	{
		this->name = name;
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
void insertion(Node*& root, Directry* dir, string name)
{
	if (root == NULL)
	{
		return;
	}
	if (root->dir->getName() == name)
	{
		if (dir->getType() == 1)
		{
			if (root->right == NULL)
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
	insertion(root->left, dir, name);
	insertion(root->right, dir, name);
}
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
		/*if (searching(root, location))
		{
			makeDeletion(root, location, type);
		}
		else
		{
			cout << "ERROR : file or directry not found!" << endl;
		}*/
	}
	// Functions for searching feature
	/*void searchAFile(Node* root, string name)
	{
		if (root == NULL)
		{
			return;
		}
		
		if (root->dir->getName() == name)
		{
			cout << "OUTPUT : ";
			wcout<<root->dir->getLocation()<<endl;
		}
		searchAFile(root->left, name);
		searchAFile(root->right, name);
	}*/
	bool searchAFile(Node* root, string name)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (root->dir->getName() == name)
		{
			return 1;
		}
		bool check1=searchAFile(root->left, name);
		bool check2=searchAFile(root->right, name);
		return check1 || check2;
	}
	// Functions for merging two directries
	bool searchADirectry(Node* root, wstring dir)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->dir->getLocation() == dir)
		{
			return 1;
		}
		bool check1 = searchADirectry(root->left, dir);
		bool check2 = searchADirectry(root->right, dir);
		return check1 || check2;
	}
	// callling inline functions and also checking the existance of source distination and different checks
	void mergeDirectries(wstring source, wstring distination, string rename)
	{
		if (checkExistenceOfMergingDirectries(head, source, distination))
		{
			Node* temp = mergeTwoDirectries(head, source, distination);
			if (temp != NULL)
			{
				insertADirectryAtGivenDis(head, temp, distination, rename);
			}
			
		}
		
	}
	bool  deleteAFile(Node*& root, string name)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->dir->getName() == name)
		{
			Node* temp = root;
			root = root->right;
			delete temp;
			return 1;
		}
		bool check1=deleteAFile(root->left, name);
		bool check2=deleteAFile(root->right, name);
		return check1 || check2;
	}
	void moveAFile(string name, wstring distination)
	{
		if (checkExistenceOfCopingAndMovingFiles(head, name, distination))
		{
			
			Node* file = returnANode(head, name);
			Node* newNode = new Node(file->dir);
			if (deleteAFile(head, name))
			{
				if (newNode != NULL)
				{
					insertAFileAtGivenDis(head, newNode, distination);
				}
			}
			else
			{
			cout << "ERROR : file did't move!" << endl;
			}

		}
	}
	void copyAFile(string name, wstring distination)
	{
		if (checkExistenceOfCopingAndMovingFiles(head, name, distination))
		{
			Node* file=returnANode(head, name);
			if (file != NULL)
			{
				insertAFileAtGivenDis(head, file, distination);
			}
		}
	}
	// These functions are private because they are used just to help public functions 
	//accessing these functions in main does not make any sense
private:
	// function which check space at given distination
	bool checkSpaceForDirectry(Node* root, wstring distination)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->dir->getLocation() == distination)
		{
			if (root->left == NULL)
			{
				return 1;
			}
		}
		bool check1 = checkSpaceForDirectry(root->left, distination);
		bool check2 = checkSpaceForDirectry(root->right, distination);
		return check1 || check2;
	}
	bool checkSpaceForFile(Node* root, wstring distination)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (root->dir->getLocation() == distination)
		{
			if (root->right == NULL)
			{
				return 1;
			}
		}
		bool check1 = checkSpaceForFile(root->left, distination);
		bool check2 = checkSpaceForFile(root->right, distination);
		return check1 || check2;
	}
	bool checkExistenceOfCopingAndMovingFiles(Node* root, string name, wstring distination)
	{
		if (searchAFile(root, name) && searchADirectry(root, distination))
		{
			if (checkSpaceForFile(root, distination))
			{
				return 1;
			}
			else
			{
				cout << "ERROR : directry is ful" << endl;
				return 0;
			}
		}
		else
		{
			cout << "ERROR :  file or directry not exists!" << endl;
			return 0;
		}
	}
	bool checkExistenceOfMergingDirectries(Node* root, wstring source, wstring distination)
	{
		if (searchADirectry(root, source) && searchADirectry(root, distination))
		{
			if (checkSpaceForDirectry(root, distination))
			{
				return 1;
			}
			else
			{
				cout << "ERROR : directry is full" << endl;
				return 0;
			}
		}
		else
		{
			cout << "ERROR : directry not exists!" << endl;
			return 0;
		}
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

		bool left = searching(root->left, path);
		bool right = searching(root->right, path);
		if (left || right)
		{
			return 1;
		}
		return 0;
	}
	Node* returnANode(Node* root, string name)
	{
		if (root == NULL)
		{
			return nullptr;
		}
		if (root->dir->getName() == name)
		{
			return root;
		}
		Node* left = returnANode(root->left, name);
		Node* right = returnANode(root->right, name);
		if (left != NULL)
		{
			return left;
		}
		else
		{
			return right;
		}

	}
	void insertAFileAtGivenDis(Node*& root, Node* insertingNode, wstring dis)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->dir->getLocation() == dis)
		{
			root->right = insertingNode;
		}

		insertAFileAtGivenDis(root->left, insertingNode, dis);
		insertAFileAtGivenDis(root->right, insertingNode, dis);

	}
	void insertADirectryAtGivenDis(Node*& root,Node* insertingNode, wstring dis, string rename)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->dir->getLocation() == dis)
		{
			root->dir->setName(rename);
			root->left = insertingNode;
		}

		insertADirectryAtGivenDis(root->left, insertingNode, dis, rename);
		insertADirectryAtGivenDis(root->right, insertingNode, dis, rename);
	}
	void deleteTree(Node*& root) {
		if (root == NULL) {
			return;
		}
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
	void makeDublicate(Node* root, Node*& newNode)
	{
		if (root == NULL)
		{
			return;
		}
		newNode = new Node(root->dir);
		makeDublicate(root->left, newNode->left);
		makeDublicate(root->right, newNode->right);
	}
	Node* mergeTwoDirectries(Node*& root, wstring sourceLoc, wstring distLoc) {
		if (root == nullptr) {
			return NULL;
		}

		if (root->dir->getLocation() == sourceLoc) {
			Node* temp = nullptr;
			if (root->left != nullptr || root->right != nullptr) {
				makeDublicate(root, temp);
				deleteTree(root);
				root = nullptr;
				return temp;
				
			}
			else {
				deleteTree(root);
				root = nullptr;
				return temp;
			}
			
			
		}

		Node* l=mergeTwoDirectries(root->left, sourceLoc, distLoc);
		Node* r=mergeTwoDirectries(root->right, sourceLoc, distLoc);
		if (l != NULL)
		{
			return l;
		}
		return r;
	}

	//void makeDeletion(Node* root, wstring locat, bool type)
	//{
		//if (root == NULL)
		//{
		//	return;
		//}
		//if (root->dir->getLocation() == locat)
		//{
		//	if (root->left == NULL && root->right == NULL)
		//	{
		//		if (type == 0)
		//		{
		//			deleteADirectry(locat);
		//		}
		//		else
		//		{
		//			locale loc;
		//			wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		//			// Convert wstring to string
		//			string location = converter.to_bytes(locat);
		//			deleteAFile(location);
		//		}
		//			
		//		delete root;
		//	}
		//	else
		//	{
		//		int input;
		//		cout << "WARNING : there is some data in this specific location\ndo you want to merge with other directry? \npress 1 to merge or press 0 if you don't want to merge." << endl;
		//		cin >> input;
		//		if (input)
		//		{
		//			if (type == 0)
		//				deleteADirectry(locat);
		//			else
		//			{
		//				locale loc;
		//				wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		//				// Convert wstring to string
		//				string location = converter.to_bytes(locat);
		//				deleteAFile(location);
		//			}
		//				
		//			delete root;
		//		}
		//	}
		//}
		//makeDeletion(root->left, locat, type);
		//makeDeletion(root->right, locat, type);
	//}
	
};