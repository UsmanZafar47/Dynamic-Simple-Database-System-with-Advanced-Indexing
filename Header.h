#pragma once

#include<iostream>
#include<queue>
#include<stack>
#include<fstream>
#include<sstream>

using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}



template<typename T>
class node {
public:
	int data;
	int year, death;
	float deathrate;
	string cause;
	string state;
	string cause_113;
	int line_no;
	string filename;

	node<T>* next;
	node<T>* left, * right;
	int height;
	int count;
	int getHeight() {
		if (!this)
			return 0;
		return height;
	}
	int getBalance() {
		if (!this)
			return 0;
		return left->getHeight() - right->getHeight();
	}

	node(int d = 0, int year = 0, string cause_113 = "", string cause = "", string state = "", int death = 0, float deathrate = 0.0, int line_no = 0, string filename = "") {
		data = d;
		this->year = year;
		this->cause = cause;
		this->cause_113 = cause_113;
		this->state = state;
		this->death = death;
		this->deathrate = deathrate;
		this->line_no = line_no;
		this->filename = filename;

		left = right = nullptr;
		next = nullptr;
		height = 1;
		count = 1;
	}

	int get_data()
	{
		return data;
	}

	int get_death()
	{
		return death;
	}
	int get_year()
	{
		return year;
	}
	string get_state()
	{
		return state;
	}
	string get_cause()
	{
		return cause;
	}
	float get_deathrate()
	{
		return deathrate;
	}


	int Height() {
		return Height(this);
	}
	int Height(node<T>* root) const {
		if (root == NULL)
			return 0;
		else {
			int left_height = Height(root->left);
			int right_height = Height(root->right);
			return max(left_height, right_height) + 1;
		}
	}
	bool isAVL() {
		return isAVL(this);
	}
	bool isAVL(node<T>* tree) {
		if (!tree)
			return true;
		if (tree->left->Height() - tree->right->Height() > 1 || tree->left->Height() - tree->right->Height() < -1)
			return false;
		if (!isAVL(tree->left))
			return false;
		if (!isAVL(tree->right))
			return false;
		return true;
	}
};





template<typename T>
class AVLbst {
	node<T>* root;


	void deleterecord(string filename, int lineNum) {


		cout << filename << " " << lineNum << endl;

		ifstream file;
		file.open(filename.c_str());
		ofstream temp;
		//temp.open("temp.csv");
		string line;
		int count1 = 0;

		// if (!file.is_open())cout << "masla" << endl;
		temp.open("temp.csv");
		while (getline(file, line))
		{
			if (count1 == lineNum)
			{
				cout << "checklol" << endl;
			}
			else
			{
				temp << line << endl;
			}
			count1++;
		}
		file.close();
		temp.close();
		remove(filename.c_str());
		rename("temp.csv", filename.c_str());
		if (rename("temp.csv", filename.c_str()) == -1) {
			cout << "unsuccessful" << endl;
		}
		else
			cout << "Yas" << endl;



	}

	//////
	//// DELETION
	//ID DELETION
	//// DELETION
	///////
	node<T>* Delete(T key, node<T>* root)
	{
		if (!root)
			return nullptr;



		if (key < root->data)
			root->left = Delete(key, root->left);
		else if (key > root->data)
			root->right = Delete(key, root->right);
		else {
			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;

				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\Id\\" + to_string(root->data) + ".txt";

				my_file.open(filename);
				while (!my_file.eof())
				{
					getline(my_file, line);
					fname = line;
					getline(my_file, line2);
					line_no = stoi(line2);

					deleterecord(fname, line_no);
					my_file.close();
				}

				node<T>* tmp = root;
				root = root->left ? root->left : root->right;
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
			}
			else {

				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;

				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\Id\\" + to_string(root->data) + ".txt";

				my_file.open(filename);
				while (!my_file.eof())
				{
					getline(my_file, line);
					fname = line;
					getline(my_file, line2);
					line_no = stoi(line2);

					deleterecord(fname, line_no);
					my_file.close();
				}



				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->data = tmp->data;
				root->count = tmp->count;
				tmp->count = 1;

				root->right = Delete(tmp->data, root->right);


			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}



	node<T>* Delete_year(T key, node<T>* root)
	{
		if (!root)
			return nullptr;
		if (key < root->year)
			root->left = Delete_year(key, root->left);
		else if (key > root->year)
			root->right = Delete_year(key, root->right);
		else {


			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\year\\" + to_string(root->year) + ".txt";


				my_file.open(filename);
				//while (!my_file.eof())
				//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);
				deleterecord(fname, line_no);

				//}

				node<T>* tmp = root;
				root = root->left ? root->left : root->right;//if(root=root->left) {root->left }else{root->right} 
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
				//		my_file.close();

			}
			else {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\year\\" + to_string(root->year) + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				//}




				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->year = tmp->year;
				root->count = tmp->count;
				tmp->count = 1;
				//my_file.close();
				root->right = Delete_year(tmp->year, root->right);

			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}


	node<T>* Delete_state(T key, node<T>* root)
	{
		if (!root)
			return nullptr;
		if (key < root->state)
			root->left = Delete_state(key, root->left);
		else if (key > root->state)
			root->right = Delete_state(key, root->right);
		else {
			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {

				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\states\\" + root->state + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				node<T>* tmp = root;
				root = root->left ? root->left : root->right;
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
			}
			else {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\states\\" + root->state + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->state = tmp->state;
				root->count = tmp->count;
				tmp->count = 1;
				root->right = Delete_state(tmp->state, root->right);
			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}


	node<T>* Delete_cause(T key, node<T>* root)
	{
		if (!root)
			return nullptr;
		if (key < root->state)
			root->left = Delete_cause(key, root->left);
		else if (key > root->state)
			root->right = Delete_cause(key, root->right);
		else {
			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {

				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\causes\\" + root->cause + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				node<T>* tmp = root;
				root = root->left ? root->left : root->right;
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
			}
			else {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\causes\\" + root->cause + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);


				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->cause = tmp->cause;
				root->count = tmp->count;
				tmp->count = 1;
				root->right = Delete_cause(tmp->cause, root->right);
			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

	node<T>* Delete_death(T key, node<T>* root)
	{
		if (!root)
			return nullptr;
		if (key < root->death)
			root->left = Delete_death(key, root->left);
		else if (key > root->death)
			root->right = Delete_death(key, root->right);
		else {
			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {

				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\deaths\\" + to_string(root->death) + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				node<T>* tmp = root;
				root = root->left ? root->left : root->right;
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
			}
			else {

				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\deaths\\" + to_string(root->death) + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);

				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->death = tmp->death;
				root->count = tmp->count;
				tmp->count = 1;
				root->right = Delete_death(tmp->death, root->right);
			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

	node<T>* Delete_deathrate(T key, node<T>* root)
	{
		if (!root)
			return nullptr;
		if (key < root->deathrate)
			root->left = Delete_deathrate(key, root->left);
		else if (key > root->deathrate)
			root->right = Delete_deathrate(key, root->right);
		else {
			if (root->count > 1) {
				(root->count)--;
				return root;
			}
			if (!root->left || !root->right) {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\death_rates\\" + to_string(root->deathrate) + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);


				node<T>* tmp = root;
				root = root->left ? root->left : root->right;
				if (!tmp) {
					tmp = root;
					root = nullptr;
				}
				delete tmp;
			}
			else {


				ifstream my_file;
				string filename;
				string line = "", fname;
				string line2 = "";
				int line_no = 0;
				filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\death_rates\\" + to_string(root->deathrate) + ".txt";

				my_file.open(filename);
				//	while (!my_file.eof())
					//{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				deleterecord(fname, line_no);


				node<T>* tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->deathrate = tmp->deathrate;
				root->count = tmp->count;
				tmp->count = 1;
				root->right = Delete_deathrate(tmp->death, root->right);
			}
		}
		if (!root)
			return root;
		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		if (balance > 1 && root->left->getBalance() >= 0)
			return rightRotate(root);
		if (balance > 1 && root->left->getBalance() < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && root->right->getBalance() <= 0)
			return leftRotate(root);
		if (balance > 1 && root->right->getBalance() > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	///
	//
	//
	//indexing
	//
	//
	///
	void idindex(node<T>* root)
	{
		ofstream my_file;
		if (root == NULL)
			return;


		idindex(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\Id\\" + to_string(root->data) + ".txt");

		my_file << root->filename << endl;
		my_file << root->line_no << endl;

		if (root->left != NULL)
		{
			my_file << to_string(root->left->data) + ".txt" << endl;
		}
		if (root->right != NULL)
		{
			my_file << to_string(root->right->data) + ".txt" << endl;
		}

		idindex(root->right);
	}

	void year_index(node<T>* root)
	{
		ofstream my_file;

		if (root == NULL)
			return;


		year_index(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\year\\" + to_string(root->year) + ".txt");



		if (root->next != NULL)
		{
			node<T>* temp = root;

			while (temp != NULL)
			{
				my_file << temp->filename << endl;
				my_file << temp->line_no << endl;
				temp = temp->next;
			}
		}
		year_index(root->right);

	}

	void death_index(node<T>* root)
	{
		int i = 0;
		ofstream my_file;

		if (root == NULL)
			return;


		death_index(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\deaths\\" + to_string(root->death) + ".txt");

		my_file << root->filename << endl;
		my_file << root->line_no << endl;

		if (root->next != NULL)
		{
			node<T>* temp = root;

			while (temp != NULL)
			{
				if (i == 0)
				{
					temp = temp->next;
					i++;
					continue;
				}my_file << temp->filename << endl;
				my_file << temp->line_no << endl;
				temp = temp->next;
			}
		}
		death_index(root->right);

	}


	void deathrate_index(node<T>* root)
	{
		int i = 0;
		ofstream my_file;

		if (root == NULL)
			return;


		deathrate_index(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\death_rates\\" + to_string(root->deathrate) + ".txt");

		my_file << root->filename << endl;
		my_file << root->line_no << endl;

		if (root->next != NULL)
		{
			node<T>* temp = root;

			while (temp != NULL)
			{
				if (i == 0)
				{
					temp = temp->next;
					i++;
					continue;
				}
				my_file << temp->filename << endl;
				my_file << temp->line_no << endl;
				temp = temp->next;
			}
		}
		deathrate_index(root->right);

	}

	void cause_index(node<T>* root)
	{
		int i = 0;
		ofstream my_file;

		if (root == NULL)
			return;


		cause_index(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\causes\\" + root->cause + ".txt");

		my_file << root->filename << endl;
		my_file << root->line_no << endl;

		if (root->next != NULL)
		{
			node<T>* temp = root;

			while (temp != NULL)
			{
				if (i == 0)
				{
					temp = temp->next;
					i++;
					continue;
				}
				my_file << temp->filename << endl;
				my_file << temp->line_no << endl;
				temp = temp->next;
			}
		}
		cause_index(root->right);

	}


	void state_index(node<T>* root)
	{
		int i = 0;
		ofstream my_file;

		if (root == NULL)
			return;


		state_index(root->left);
		my_file.open("C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\states\\" + root->state + ".txt");

		my_file << root->filename << endl;
		my_file << root->line_no << endl;

		if (root->next != NULL)
		{
			node<T>* temp = root;

			while (temp != NULL)
			{
				if (i == 0)
				{
					temp = temp->next;
					i++;
					continue;
				}
				my_file << temp->filename << endl;
				my_file << temp->line_no << endl;
				temp = temp->next;
			}
		}
		state_index(root->right);

	}
	//
	//
	//
	//
	//indexing  end
	//
	// 
	// 
	// 
	// 

	//data = id
	node<T>* insert(int data, node<T>* root, int year, string cause_113, string cause, string state, int death, float deathrate, string filename, int line_no, int choice) {

		node<T>* root_file;
		if (!root)
			return new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
		if (data == root->data) {
			(root->count)++;
			return root;
		}
		if (choice == 1)
		{
			root_file = root;
			if (root->data > data)
			{
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			}
			else
			{
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			}
		}
		if (choice == 2)//year insertion
		{
			if (root->year > year)
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->year < year)
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->year == year)
			{
				node<T>* newNode = new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
				newNode->year = year;
				newNode->next = NULL;

				if (root == NULL)
					root = newNode;
				else
				{
					node<T>* lastNode = root;
					while (lastNode->next != NULL)
					{
						lastNode = lastNode->next;
					}
					lastNode->next = newNode;
				}
				//				root->next = insert(data, root->right, year, cause, state, death, deathrate, choice);

			}

		}

		if (choice == 3)//making list of duplicates
		{
			if (root->cause > cause)
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->cause < cause)
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->cause == cause)
			{
				node<T>* newNode = new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
				newNode->cause = cause;
				newNode->next = NULL;

				if (root == NULL)
					root = newNode;
				else
				{
					node<T>* lastNode = root;
					while (lastNode->next != NULL)
					{
						lastNode = lastNode->next;
					}
					lastNode->next = newNode;
				}
			}



		}

		if (choice == 4)//state insertion
		{
			if (root->state > state)
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->state < state)
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->state == state)
			{
				node<T>* newNode = new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
				newNode->state = state;
				newNode->next = NULL;

				if (root == NULL)
					root = newNode;
				else
				{
					node<T>* lastNode = root;
					while (lastNode->next != NULL)
					{
						lastNode = lastNode->next;
					}
					lastNode->next = newNode;
				}
			}
		}

		if (choice == 5)
		{
			if (root->death > death)
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->death < death)
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->death == death)
			{
				if (root->death > death)
					root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
				else if (root->death < death)
					root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
				else if (root->death == death)
				{
					node<T>* newNode = new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
					newNode->death = death;
					newNode->next = NULL;

					if (root == NULL)
						root = newNode;
					else
					{
						node<T>* lastNode = root;
						while (lastNode->next != NULL)
						{
							lastNode = lastNode->next;
						}
						lastNode->next = newNode;
					}
				}
				//		


			}
		}
		if (choice == 6)
		{
			if (root->deathrate > deathrate)
				root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->deathrate < deathrate)
				root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
			else if (root->deathrate == deathrate)
			{
				if (root->deathrate > deathrate)
					root->left = insert(data, root->left, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
				else if (root->deathrate < deathrate)
					root->right = insert(data, root->right, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
				else if (root->deathrate == deathrate)
				{
					node<T>* newNode = new node<T>(data, year, cause_113, cause, state, death, deathrate, line_no, filename);
					newNode->deathrate = deathrate;
					newNode->next = NULL;

					if (root == NULL)
						root = newNode;
					else
					{
						node<T>* lastNode = root;
						while (lastNode->next != NULL)
						{
							lastNode = lastNode->next;
						}
						lastNode->next = newNode;
					}
				}
				//		




			}
		}



		root->height = max(root->left->getHeight(), root->right->getHeight()) + 1;
		int balance = root->getBalance();
		//1 for ID insertion
		if (choice == 1) {
			if (balance > 1 && data < root->left->data)
				return rightRotate(root);
			if (balance < -1 && data > root->right->data)
				return leftRotate(root);
			if (balance > 1 && data > root->left->data) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && data < root->right->data) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}
		//2 for year insertion
		if (choice == 2) {
			if (balance > 1 && year < root->left->year)
				return rightRotate(root);
			if (balance < -1 && year > root->right->year)
				return leftRotate(root);
			if (balance > 1 && year > root->left->year) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && year < root->right->year) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}
		if (choice == 3) {
			if (balance > 1 && cause < root->left->cause)
				return rightRotate(root);
			if (balance < -1 && cause > root->right->cause)
				return leftRotate(root);
			if (balance > 1 && cause > root->left->cause) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && cause < root->right->cause) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}

		if (choice == 4) {
			if (balance > 1 && state < root->left->state)
				return rightRotate(root);
			if (balance < -1 && state > root->right->state)
				return leftRotate(root);
			if (balance > 1 && state > root->left->state) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && state < root->right->state) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}


		if (choice == 5) {
			if (balance > 1 && death < root->left->death)
				return rightRotate(root);
			if (balance < -1 && death > root->right->death)
				return leftRotate(root);
			if (balance > 1 && death > root->left->death) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && death < root->right->death) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}

		if (choice == 6) {
			if (balance > 1 && deathrate < root->left->deathrate)
				return rightRotate(root);
			if (balance < -1 && deathrate > root->right->deathrate)
				return leftRotate(root);
			if (balance > 1 && deathrate > root->left->deathrate) {
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
			if (balance < -1 && deathrate < root->right->deathrate) {
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}

		return root;
	}

	void display_file(string fileName, int line_no)
	{
		fstream my_file;
		string tp;
		string line = " ";
		int id{};
		string year;
		string cause;
		string state;
		string deaths;
		string cause113;
		double ad{};
		double aadr{};
		string temp = " ";

		my_file.open(fileName);

		for (int i = 0; i < line_no; i++)
		{
			getline(my_file, tp);
		}

		getline(my_file, tp);

		stringstream inputs(tp);

		getline(inputs, temp, ',');
		id = atoi(temp.c_str());
		getline(inputs, year, ',');
		getline(inputs, cause, ',');
		getline(inputs, cause113, ',');
		getline(inputs, state, ',');
		getline(inputs, deaths, ',');

		temp = " ";
		getline(inputs, temp, ',');
		ad = atof(temp.c_str());
		getline(inputs, temp, ',');

		aadr = atof(temp.c_str());

		cout << id << " " << year << " " << cause << " " << cause113 << " " << state << " " << deaths << " " << aadr << endl;

		my_file.close();
	}

	bool search(T data, node<T>* root) {
		if (!root)
			return false;
		if (data == root->data)
		{
			ifstream my_file;
			string filename;
			string line, fname;
			string line2;
			int line_no;

			if (root == NULL)
				return false;


			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\Id\\" + to_string(root->data) + ".txt";
			my_file.open(filename);
			getline(my_file, line);
			fname = line;
			getline(my_file, line2);
			line_no = stoi(line2);

			display_file(fname, line_no);

			return root;
		}
		if (data < root->data)
		{
			return search(data, root->left);
		}
		return search(data, root->right);
	}

	bool searchyear(int year, node<T>* root) {
		if (!root)
			return false;
		if (year == root->year)
		{
			//	printdata(root);
			ifstream my_file;
			string filename;
			string line = "", fname;
			string line2 = "";
			int line_no = 0;

			if (root == NULL)
				return false;

			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\year\\" + to_string(root->year) + ".txt";

			my_file.open(filename);
			while (!my_file.eof())
			{
				getline(my_file, line);//reading file name
				fname = line;
				getline(my_file, line2);//reading line no
				line_no = stoi(line2);

				display_file(fname, line_no);
			}

			return root;
		}
		if (year < root->year)
		{
			return searchyear(year, root->left);
		}
		return searchyear(year, root->right);
	}

	bool searchstate(string state, node<T>* root) {
		if (!root)
			return false;
		if (state == root->state)
		{
			//printdata(root);

			ifstream my_file;
			string filename;
			string line = "", fname;
			string line2 = "";
			int line_no = 0;

			if (root == NULL)
				return false;

			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\states\\" + root->state + ".txt";

			my_file.open(filename);
			while (!my_file.eof())
			{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				display_file(fname, line_no);
			}


			return root;
		}
		if (state < root->state)
		{
			return searchstate(state, root->left);
		}
		return searchstate(state, root->right);
	}

	bool search_cause(string cause, node<T>* root)
	{
		//return searchstate(cause,root);

		if (!root)
			return false;
		if (cause == root->cause)
		{
			//	printdata(root);


			ifstream my_file;
			string filename;
			string line = "", fname;
			string line2 = "";
			int line_no = 0;

			if (root == NULL)
				return false;

			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\causes\\" + root->cause + ".txt";

			my_file.open(filename);
			while (!my_file.eof())
			{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				display_file(fname, line_no);
			}



			return root;
		}
		if (cause < root->cause)
		{
			return search_cause(cause, root->left);
		}
		return search_cause(cause, root->right);

	}

	bool search_death(int death, node<T>* root)
	{
		if (!root)
			return false;
		if (death == root->death)
		{
			//printdata(root);

			ifstream my_file;
			string filename;
			string line = "", fname;
			string line2 = "";
			int line_no = 0;

			if (root == NULL)
				return false;

			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\deaths\\" + to_string(root->death) + ".txt";

			my_file.open(filename);
			while (!my_file.eof())
			{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				display_file(fname, line_no);
			}

			return root;
		}
		if (death < root->death)
		{
			return search_death(death, root->left);
		}
		return search_death(death, root->right);
	}

	bool search_deathrate(float deathrate, node<T>* root)
	{
		if (!root)
			return false;
		if (deathrate == root->deathrate)
		{
			//	printdata(root);

			ifstream my_file;
			string filename;
			string line = "", fname;
			string line2 = "";
			int line_no = 0;

			if (root == NULL)
				return false;

			filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\death_rates\\" + to_string(root->deathrate) + ".txt";

			my_file.open(filename);
			while (!my_file.eof())
			{
				getline(my_file, line);
				fname = line;
				getline(my_file, line2);
				line_no = stoi(line2);

				display_file(fname, line_no);
			}

			return root;
		}
		if (deathrate < root->deathrate)
		{
			return search_deathrate(deathrate, root->left);
		}
		return search_deathrate(deathrate, root->right);
	}



	//Range search by ID
	void rangesearch(int start, int end, node<T>* root)
	{
		if (!root)
			return;
		for (int i = start; i <= end; i++)
		{
			int lineno = 0;

			string line = " ";
			int id{};
			string year;
			string cn;
			string st;
			string deaths;
			string c113;
			double ad{};
			double aadr{};
			string temp = " ";

			string fName = "";
			string tp;
			fstream file;
			string filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\Id\\" + to_string(i) + ".txt";
			//cout << filename << endl;
			//cout << filename << endl;

			file.open(filename);
			if (!file.is_open()) { cout << "masla" << endl; }
			getline(file, tp);
			fName = tp;
			getline(file, tp);
			lineno = stoi(tp);

			//  cout << fName << " " << lineno << endl;

			file.close();

			display_file(fName, lineno);

		}

	}

	//Range search by year
	void rangesearchyear(int start, int end, node<T>* root)
	{
		if (!root)
			return;

		system("cls");
		for (int i = start; i <= end; i++)
		{
			int lineno = 0;

			string line = " ";
			int id{};
			string year;
			string cn;
			string st;
			string deaths;
			string c113;
			double ad{};
			double aadr{};
			string temp = " ";

			string fName = "";
			string tp;
			fstream file;
			string filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\year\\" + to_string(i) + ".txt";
			//cout << filename << endl;
			//cout << filename << endl;

			file.open(filename);
			if (!file.is_open()) { cout << "masla" << endl; }
			while (!file.eof()) {
				getline(file, tp);
				fName = tp;
				getline(file, tp);
				lineno = stoi(tp);

				//  cout << fName << " " << lineno << endl;


				display_file(fName, lineno);

			}
			file.close();

			//	printdata(root);
		}

	}
	//Range search by deaths
	void rangesearch_death(int start, int end, node<T>* root)
	{
		if (!root)
			return;

		system("cls");
		for (int i = start; i <= end; i++)
		{
			//search_death(i, root);

			int lineno = 0;

			string line = " ";
			int id{};
			string year;
			string cn;
			string st;
			string deaths;
			string c113;
			double ad{};
			double aadr{};
			string temp = " ";

			string fName = "";
			string tp;
			fstream file;
			string filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\deaths\\" + to_string(i) + ".txt";
			//cout << filename << endl;
			//cout << filename << endl;

			file.open(filename);
			if (!file.is_open()) { cout << "masla" << endl; }
			while (!file.eof()) {
				getline(file, tp);
				fName = tp;
				getline(file, tp);
				if (tp != "")
					lineno = stoi(tp);

				//  cout << fName << " " << lineno << endl;


				display_file(fName, lineno);

			}
			file.close();



			//	printdata(root);
		}


	}


	void maxElement(node<T>* root, queue<T>& q) {
		if (root->right)
			maxElement(root->right, q);
		q.push(root->data);
		if (root->left)
			maxElement(root->left, q);
	}
	void postorder(node<T>* root) {
		if (!root)
			return;
		postorder(root->left);
		postorder(root->right);
		cout << root->data << " ";
	}


	void create(node<T>* root, string name, int data, int year, string cause, string state, int death, float deathrate)
	{
		ofstream fout;

		fout.open(name, ios::app);

		fout << data << ", " << year << ", " << cause << ", " << state << ", " << death << ", " << deathrate << "\n";

		fout.close();

	}


	void create_delete(node<T>* root, string name, int data)
	{
		string line;
		ifstream fin;
		ofstream fout;
		fin.open(name);
		fout.open("new.csv", ios::app);

		cin >> name;

		while (!fin.eof()) {
			if (line.find(name) == data)
			{
				fout << root->data << ", " << root->year << ", " << root->cause << ", " << root->state << ", " << root->death << ", " << root->deathrate << "\n";
			}
		}
		fout.close();
		fin.close();


		/*ofstream fout;

		fout.open(name, ios::app);

		fout << data << ", " << year << ", " << cause << ", " << state << ", " << death << ", " << deathrate << "\n";

		fout.close();*/

		remove("idtree.csv");
		rename("new.csv", "idtree.csv");
		cout << "\nChanges has Successfully been made...... Data Saved\n" << endl;


	}



public:

	/*void create(string name)
	{
		create(root,name);

	}*/


	string Get_nthWord(string s, int n)
	{
		int counter = 0;
		string temp;
		int i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == ',')
			{
				counter++;
			}

			else if (counter == n - 1)
			{
				temp += s[i];
			}
			i++;
		}
		return temp;
	}

	void update(string filename, int lineNum, string newdata, int choice) {
		ifstream file;
		file.open(filename.c_str());
		ofstream temp;
		string	filename2 = "temp.csv";
		temp.open(filename2);
		string line;
		int count = 0;

		while (getline(file, line)) {
			if (count == lineNum) {

				if (choice == 1) {
					string id = Get_nthWord(line, 1);
					string year = Get_nthWord(line, 2);
					string c113 = Get_nthWord(line, 3);

					//string cn = Get_nthWord(line, 4);
					//string state = Get_nthWord(line, 5);
					//string deaths = Get_nthWord(line, 6);
					//string adr = Get_nthWord(line, 7);

					////cout << id << "," << year << "," << c113 << "," << cn << "," << newdata << "," << deaths << "," << adr << endl;

					//temp << id << "," << year << "," << c113 << "," << cn << "," << newdata << "," << deaths << "," << adr << endl;


					string lol = Get_nthWord(line, 4);
					string cn = Get_nthWord(line, 5);
					string state = Get_nthWord(line, 6);
					string deaths = Get_nthWord(line, 7);
					string adr = Get_nthWord(line, 8);
					temp << id << "," << year << "," << c113 << "," << lol << "," << cn << "," << newdata << "," << deaths << "," << adr << endl;
				}
				if (choice == 2)
				{

					string id = Get_nthWord(line, 1);
					string year = Get_nthWord(line, 2);
					string c113 = Get_nthWord(line, 3);
					int year_int = stoi(newdata);

					//string cn = Get_nthWord(line, 4);
					//string state = Get_nthWord(line, 5);
					//string deaths = Get_nthWord(line, 6);
					//string adr = Get_nthWord(line, 7);

					////cout << id << "," << year_int << "," << c113 << "," << cn << "," << state << "," << deaths << "," << adr << endl;

					//temp << id << "," << year_int << "," << c113 << "," << cn << "," << state << "," << deaths << "," << adr << endl;


					string lol = Get_nthWord(line, 4);
					string cn = Get_nthWord(line, 5);
					string state = Get_nthWord(line, 6);
					string deaths = Get_nthWord(line, 7);
					string adr = Get_nthWord(line, 8);
					temp << id << "," << year_int << "," << c113 << "," << lol << "," << cn << "," << state << "," << deaths << "," << adr << endl;

				}
				if (choice == 3)
				{

					string id = Get_nthWord(line, 1);
					string year = Get_nthWord(line, 2);
					string c113 = Get_nthWord(line, 3);

					//string cn = Get_nthWord(line, 4);
					//string state = Get_nthWord(line, 5);
					//string deaths = Get_nthWord(line, 6);
					//string adr = Get_nthWord(line, 7);

					////cout << id << "," << year << "," << c113 << "," << newdata << "," << state << "," << deaths << "," << adr << endl;

					//temp << id << "," << year << "," << c113 << "," << newdata << "," << state << "," << deaths << "," << adr << endl;


					string lol = Get_nthWord(line, 4);
					string cn = Get_nthWord(line, 5);
					string state = Get_nthWord(line, 6);
					string deaths = Get_nthWord(line, 7);
					string adr = Get_nthWord(line, 8);
					temp << id << "," << year << "," << c113 << "," << lol << "," << newdata << "," << state << "," << deaths << "," << adr << endl;

				}
				if (choice == 4)
				{

					string id = Get_nthWord(line, 1);
					string year = Get_nthWord(line, 2);
					string c113 = Get_nthWord(line, 3);


					//string cn = Get_nthWord(line, 4);
					//string state = Get_nthWord(line, 5);
					//string deaths = Get_nthWord(line, 6);
					//string adr = Get_nthWord(line, 7);
					// int death_int = stoi(newdata);	
					////cout << id << "," << year << "," << c113 << "," << cn << "," << state << "," << death_int << "," << adr << endl;

					//temp << id << "," << year << "," << c113 << "," << cn << "," << state << "," << death_int << "," << adr << endl;


					string lol = Get_nthWord(line, 4);
					string cn = Get_nthWord(line, 5);
					string state = Get_nthWord(line, 6);
					string deaths = Get_nthWord(line, 7);
					int death_int = stoi(deaths);
					string adr = Get_nthWord(line, 8);
					temp << id << "," << year << "," << c113 << "," << lol << "," << cn << "," << state << "," << death_int << "," << adr << endl;

				}

				if (choice == 5)
				{

					string id = Get_nthWord(line, 1);
					string year = Get_nthWord(line, 2);
					string c113 = Get_nthWord(line, 3);

					//string cn = Get_nthWord(line, 4);
					//string state = Get_nthWord(line, 5);
					//string deaths = Get_nthWord(line, 6);
					//string adr = Get_nthWord(line, 7);
					//int adr_int = stof(adr);
					////cout << id << "," << year << "," << c113 << "," << cn << "," << state << "," << deaths << "," << adr_int << endl;

					//temp << id << "," << year << "," << c113 << "," << cn << "," << state << "," << newdata << "," << adr_int << endl;


					string lol = Get_nthWord(line, 4);
					string cn = Get_nthWord(line, 5);
					string state = Get_nthWord(line, 6);
					string deaths = Get_nthWord(line, 7);
					string adr = Get_nthWord(line, 8);
					int adr_int = stof(adr);
					temp << id << "," << year << "," << c113 << "," << lol << "," << cn << "," << state << "," << deaths << "," << adr_int << endl;

				}


			}
			else {

				temp << line << endl;
			}
			count++;
		}
		file.close();
		temp.close();
		remove(filename.c_str());
		rename(filename2.c_str(), filename.c_str());
		if (rename(filename2.c_str(), filename.c_str()) == -1) {
			//cout << "unsuccessful" << endl;
		}
		else {}
		// cout << "Yas" <<�endl;



	}

	void update_state(int state, string path, string newdata, int c)
	{
		string filename = "C:\\Users\\Usman's PC\\source\\repos\\DSProjectAVL\\DSProjectAVL\\" + path + "\\" + to_string(state) + ".txt";

		cout << filename;
		ifstream file;
		string tuple1, tuple2;
		int lineNum;
		file.open(filename.c_str());

		if (!file.is_open())
			cout << "file not opening" << endl;

		getline(file, tuple1);
		getline(file, tuple2);
		lineNum = stoi(tuple2);

		update(tuple1, lineNum, newdata, c);

	}



	void create(string name, int data, int year, string cause, string state, int death, float deathrate)
	{
		create(root, name, data, year, cause, state, death, deathrate);

	}

	void create_delete(string name, int data)
	{
		create_delete(root, name, data);

	}

	AVLbst() {
		root = nullptr;
	}

	void insert(int data, int year, string cause_113, string cause, string state, int death, float deathrate, string filename, int line_no, int choice)
	{
		root = insert(data, root, year, cause_113, cause, state, death, deathrate, filename, line_no, choice);
	}




	node<T>* leftRotate(node<T>* n) {
		node<T>* r = n->right;
		node<T>* tmp = r->left;
		r->left = n;
		n->right = tmp;
		n->height = max(n->left->getHeight(), n->right->getHeight()) + 1;
		r->height = max(r->left->getHeight(), r->right->getHeight()) + 1;
		return r;
	}
	node<T>* rightRotate(node<T>* n) {
		node<T>* r = n->left;
		node<T>* tmp = r->right;
		r->right = n;
		n->left = tmp;
		n->height = max(n->left->getHeight(), n->right->getHeight()) + 1;
		r->height = max(r->left->getHeight(), r->right->getHeight()) + 1;
		return r;
	}
	void inorder() {
		stack<node<T>*> s;
		node<T>* curr = root;
		while (!s.empty() || curr) {
			while (curr) {
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			cout << curr->data << " ";
			curr = curr->right;
		}
	}

	void preorder() {
		stack<node<T>*> s;
		node<T>* curr = root;
		while (!s.empty() || curr) {
			while (curr) {
				cout << curr->cause << " ";
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			curr = curr->right;
		}
	}
	void postorder() {
		postorder(root);
	}
	//SEARCHING
	bool search(T key) {
		return search(key, root);
	}

	bool searchyear(int year)
	{
		return searchyear(year, root);
	}

	bool searchstate(string key)
	{
		return searchstate(key, root);
	}

	bool search_cause(string key)
	{
		return search_cause(key, root);
	}

	bool search_death(int key)
	{
		return search_death(key, root);
	}

	bool search_deathrate(float key)
	{
		return search_deathrate(key, root);
	}//SEARCH END

	//Range search
	void rangesearch(int start, int end)
	{
		rangesearch(start, end, root);
	}

	void rangesearchyear(int start, int end)
	{
		rangesearchyear(start, end, root);
	}

	void rangesearch_death(int start, int end)
	{
		rangesearch_death(start, end, root);
	}


	void printdata(node<T>* root) {
		//	system("cls");
			//cout << "ID   year     cause     state     deaths     adr" << endl;
			//if(search(data,root)==true)
		cout << root->data << "   " << root->year << "   " << root->cause_113 << "   " << root->cause << "   " << root->state << "   " << root->death << "   " << root->deathrate << endl;
		if (root->next != NULL) {
			node<T>* temp = root;
			while (temp->next != NULL) {

				temp = temp->next;
				cout << temp->data << "   " << temp->year << "   " << temp->cause_113 << "   " << temp->cause << "   " << temp->state << "   " << temp->death << "   " << temp->deathrate << endl;
			}
		}
	}

	T maxElement(int max = 1) {
		queue <T> q;
		maxElement(root, q);
		for (int i = 1; i < max; i++)
			q.pop();
		return q.front();
	}

	//indexing
	void idindex()
	{
		idindex(root);
	}

	void year_index()
	{
		year_index(root);
	}

	void death_index()
	{
		death_index(root);
	}
	void deathrate_index()
	{
		deathrate_index(root);
	}

	void cause_index()
	{
		cause_index(root);
	}

	void state_index()
	{
		state_index(root);
	}


	void deletestatefull(string state) {
		ifstream file;
		ofstream temp;

		string line;
		for (int i = 0; i < 10; i++) {

			string filename = (to_string(i + 1) + ".csv");
			string filename2 = ("temp" + to_string(i + 1) + ".csv");
			file.open(filename.c_str());
			temp.open(filename2.c_str());

			while (getline(file, line)) {
				string check = Get_nthWord(line, 5);

				if (check == state) {
					//cout << "check" << endl;
				}
				else {
					temp << line << endl;
				}
			}

			temp.close();
			file.close();
			remove(filename.c_str());
			if (rename(filename2.c_str(), filename.c_str()) == -1) {
				//cout << "unsuccessful" << endl;
			}
			else {}

		}
	}


	void deleteyearfull(int year) {

		ifstream file;
		ofstream temp;

		string line;
		for (int i = 0; i < 10; i++) {

			string filename = (to_string(i + 1) + ".csv");
			string filename2 = ("temp" + to_string(i + 1) + ".csv");
			file.open(filename.c_str());
			temp.open(filename2.c_str());

			while (getline(file, line)) {
				string check = Get_nthWord(line, 2);

				if (check == to_string(year)) {
					//cout << "check" << endl;
				}
				else {
					temp << line << endl;
				}
			}

			temp.close();
			file.close();
			remove(filename.c_str());
			rename(filename2.c_str(), filename.c_str());
			if (rename(filename2.c_str(), filename.c_str()) == -1)
			{
			}
			else {}

		}
	}


	//
	//DELETION
	//
	void Delete(T key)
	{
		root = Delete(key, root);
	}

	void Delete_year(T key)
	{
		root = Delete_year(key, root);
	}

	void Delete_state(T key)
	{
		root = Delete_state(key, root);
	}

	void Delete_death(T key)
	{
		root = Delete_death(key, root);
	}

	void Delete_deathrate(T key)
	{
		root = Delete_deathrate(key, root);
	}

	void Delete_cause(T key)
	{
		root = Delete_cause(key, root);
	}

	//END DELETION
	bool isAVL() {
		return isAVL(root);
	}
	bool isAVL(node<T>* tree) {
		if (!tree)
			return true;
		if (tree->getBalance() > 1 || tree->getBalance() < -1)
			return false;
		if (!isAVL(tree->left))
			return false;
		if (!isAVL(tree->right))
			return false;
		return true;
	}
};

