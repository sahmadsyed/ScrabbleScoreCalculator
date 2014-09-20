#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include<algorithm>
#include<fstream>

using namespace std;

struct Node {
	string word;
	Node* next;
};

class HashTable {
public :
	HashTable ();
	HashTable (int K);
	virtual ~HashTable();
	void insert (string word);
	void remove (string word);	    
	bool lookup (string word) const;
	void print () const;
	void report () const;
	static const int DefaultSize;
protected : 
	int getTableSize() const;	    
private : 
	vector<Node*> table;
	virtual int hash (string key) const = 0;
};

const int HashTable::DefaultSize = 100000;
HashTable::HashTable() : table(DefaultSize) {}
HashTable::HashTable(int K) : table(K) {}

HashTable::~HashTable(){
	for (int i=0; i<getTableSize(); i++) {
		Node* p = table[i];
		while (p!=NULL) {
			Node* temp = p;
			p = p->next;
			delete temp;
		}
	}
}

int HashTable::getTableSize() const {
	return (int) table.size();
}

void HashTable::insert(string key) {
	const int slot = hash(key);
	Node* newNode = new Node;
	newNode->word = key;
	newNode->next = table[slot];
	table[slot] = newNode;
}

bool HashTable::lookup (string key) const {
	const int slot = hash(key);
	Node* curNode = table[slot];
	while (curNode != NULL) {
		if (curNode->word == key) {
			return true;
		}
		curNode = curNode -> next;
	}
	return false;
}

void HashTable::remove(string key) {
	int count = hash(key);
	Node* a; 
	while (true)
	{	
		a = table[count];	
		if (a->word == key)
		{
			Node* b = a;
			table[count] = a->next;
			delete b;
			break;
		}
		else if (a->next != NULL)
		{
			while ((NULL != a->next)&&(key != a->next->word))
				a = a->next;
			if (NULL != a->next)
			{
				Node* b = a->next;
				a->next = a->next->next;
				delete b;
			}
			break;
		}
		count ++;
	}
}

void HashTable::print() const {
	for (int i=0; i<getTableSize(); i++) {
		if (table[i] != NULL) {
			Node* p = table[i];
			while (p != NULL) {
				cout << i << "    " << p->word << endl;
				p = p->next;
			}
		}
	}
}

class SmartHashTable : public HashTable {
public:
	SmartHashTable():HashTable(){};
	SmartHashTable(int K):HashTable(K){};
	virtual ~SmartHashTable();
private:
	int hash(string key) const;
};

SmartHashTable::~SmartHashTable(){};
int SmartHashTable::hash(string key) const {
	string count = "";
	char a = key[0];
	int k = 1;

	while (key != "")
	{
		k = k*29 + ((int)key[0])%10;
		if (k< getTableSize())
		{
			key = key.substr(1);
		}
		else 
		{
			k = k%getTableSize();
			key = key.substr(1);
		}
	}
	return k;
}

vector<string> addChar (const vector<string>& v, char c) {
	vector<string> ans;
	for (int i=0; i<(int)v.size() ; i++) {
		ans.push_back(c + v.at(i));
	}
	return ans;
}

vector<string> powerset (string s) {
	vector<string> ans;
	if (s.size() == 0) {
		ans.push_back("");
	} else {
		char c = s.at(0);
		string rest = s.substr(1);
		vector<string> psetRest = powerset (rest);
		ans = addChar (psetRest, c);
		ans.insert(ans.end(), psetRest.begin(), psetRest.end());
	}
	return ans;
}

int main(int argc, char *argv[])
{
	if (argc <= 1 ) { 
		cerr << "Error, no word list file name provided." << endl;
		exit(1);
	} 
	string wordlistFileName = argv[1];
	ifstream is_ifile (argv[1]); 
	if (!is_ifile) { 
		cerr << "Error, couldn't open word list file." << endl; 
		exit (1); 
	} 	SmartHashTable ht;  
	string word;  
	vector<string> wordslist;  
	while(is_ifile>>word){  
		wordslist.push_back(word);  
		ht.insert(word);  
	}  	string input;	vector<string> store;	while (cin >> input)		store.push_back(input);	int coun = 0;	while (coun != store.size())	{		vector<string> storage = powerset(store[coun]);		int count = storage.size();		int count2 = 0;		string highestWord = "";		int highestValue = 0;		while (count2 != count)		{			string k = storage[count2];			sort (k.begin(), k.end());
			do
			{
				if (ht.lookup(k) == true)
				{
					string t = k;
					int initValue = 0;
					while (k != "")
					{
						if ((k[0] == 'a')||(k[0] == 'e')||(k[0] == 'i')||(k[0] == 'u')||(k[0] == 'o')||
							(k[0] == 'n')||(k[0] == 'r')||(k[0] == 's')||(k[0] == 't')||(k[0] == 'l'))
							initValue = initValue + 1;
						else if ((k[0] == 'y')||(k[0] == 'f')||(k[0] == 'v')||(k[0] == 'w')||(k[0] == 'h'))
							initValue = initValue + 4;
						else if ((k[0] == 'm')||(k[0] == 'b')||(k[0] == 'c')||(k[0] == 'p'))
							initValue = initValue + 3;
						else if ((k[0] == 'g')||(k[0] == 'd'))
							initValue = initValue + 2;
						else if ((k[0] == 'j')||(k[0] == 'x'))
							initValue = initValue + 8;
						else if ((k[0] == 'q')||(k[0] == 'z'))
							initValue = initValue + 10;
						else if (k[0] == 'k')
							initValue = initValue + 5;

						k = k.substr(1);
					}
					if (initValue > highestValue)
					{
						highestValue = initValue;
						highestWord = t;
					}

				}

			}while (next_permutation (k.begin(), k.end()));			count2++;
		}
		if (highestWord == "")
			cout << store[coun] << ": no matches" << endl;
		else
			cout << store[coun] << ": " << highestWord << " has score of " << highestValue << endl;
		coun++;
	}
	return 0;
}