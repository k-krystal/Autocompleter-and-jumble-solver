//#ifndef SIZE
#define SIZE 26
//#endif
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;


	// Declaring the struct for nodes of Trie //
struct TrieNode
{
	char alpha;
	bool isEndOfWord;
	TrieNode* children[SIZE];
};
TrieNode* root;


	// Initialising the root //
void initializeRoot()
{
	root = new TrieNode;
	root->isEndOfWord = false;
	
	for (int i=0 ; i<SIZE ; i++)
		root->children[i] = 0;
}


	// Inserting words into the Trie by creating new nodes //
void insertWord(const string &word)
{
	TrieNode *p = root;
	for (short i=0 ; i<word.length() ; i++)
	{
		short j;
		
		for (j=0 ; j<SIZE && (p->children[j] != 0) ; )
		{
			if ((p->children[j])->alpha == word[i])
			{
				p = p->children[j];
				j=0;
				i++;
			}
			
			else
				j++;
		}
		
		TrieNode* Node = new TrieNode;
		Node->isEndOfWord = false;
		Node->alpha = word[i];
		
		for (short k=0 ; k<SIZE; k++)
			Node->children[k] = 0;
		
		p->children[j] = Node;
		p = p->children[j];
	}
	
	p->isEndOfWord = true;
}

//delete a word
void removeWord(TrieNode *root, const string &word) {
		// Base case
		if(word.size() == 0) {
			root -> isEndOfWord = false;
			return;
		}

		// Small calculation
		TrieNode *child;
		int index =  word[0] - 'a';
		if(root -> children[index] != NULL) {
			child = root -> children[index];
		}
		else {
			return;
		}
        	removeWord(child, word.substr(1));

		// Remove child Node if it is useless
		if(child -> isEndOfWord == false) {
			for(int i = 0; i < 26; i++) {
				if(child -> children[i] != NULL) {
					return;
				}
			}
			delete child;
			root -> children[index] = NULL;
		}
	}

	void removeWord(const string &word) {
		removeWord(root, word);
	}





	// Displaying the words that will be suugested //
void display(TrieNode* root, char word_suggestion[], short counts)
{
	if (root->isEndOfWord)
	{
		word_suggestion[counts] = root->alpha;
		word_suggestion[counts+1] = '\0';
		cout << "\t\t" << word_suggestion << endl;
	}
	
	for (short i=0 ; i<SIZE ; i++)
	{
		if (root->children[i] != 0)
		{
			word_suggestion[counts] = root->alpha;
			display(root->children[i], word_suggestion, counts+1);
		}
	}
}


	// Traversing the Trie to match the letters enetered //
void traverseTrie(char word[])
{
	TrieNode *p = root;
	TrieNode *prev = 0;
	int i = 0;
	int flag = 0;
	
	while (word[i] != '\0')
	{
		prev = p;
		
		for (short j=0 ; j<SIZE && p->children[j] != 0 ; j++)
		{
			if ((p->children[j])->alpha == word[i])
			{
				p = p->children[j];
				break;
			}
		}
		
		i++;
		
		if(prev == p)
		{
			cout<<"\t\t\t\t\tNo match found !"<<endl;
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
		display(p, word, --i);
}


int unscramble = 0;
static int countArray[20] = {0};


	// Searching the trie for a given permuted word and printing it if present //
void searchTrie(string searchWord)
{
	TrieNode *p = root;
	TrieNode *prev = 0;
	
	int i = 0;
	
	while (searchWord[i] != '\0')
	{
		prev = p;

		for (short j=0 ; j<SIZE ; j++)
		{
			if (p->children[j] != 0 && (p->children[j])->alpha == searchWord[i])
			{
				p = p->children[j];
				break;
			}
		}
		
		i++;
		
		if(prev == p)
			return;
	}
	
	if(p->isEndOfWord == true)
	{
		cout << searchWord << endl;
		countArray[unscramble] ++;
	}
}


char* sort(const string& str)
{
	int hashTable[26] = {0};
	char* sorted= new char[str.length()];

	for (int i=0 ; i<str.length() ; i++)
	{
		hashTable[str[i]-'a']++;
	}
	
	int len = 0;
	for (int i=0 ; i<26 ; i++)
	{
		for (int j=0 ; j<hashTable[i] ; j++)
		{
			sorted[len++] = i+97;
		}
	}
	
	return sorted;
}


void print_all_permutations(const string& s)
{
	string s1;
	s1 = sort(s);
	do {
		searchTrie(s1);
	}
	while (next_permutation(s1.begin(), s1.end()));
}

	// Opening the file to read words from it and insert the words into trie //
bool openFile()
{
	ifstream wordFile;
	wordFile.open("C:/Users/Hetarth/Desktop/file1.txt");
	
	if (!wordFile)
	{
		cout << "Couldn't open file." << endl;
		return false;
	}
	
	else
	{
		string word;
		while (!wordFile.eof())
		{
			getline(wordFile, word);
			insertWord(word);
		}
		return true;
	}
}

int main()
{
	initializeRoot();
	
	if(openFile())
	{
		int choice = 0;
		cout << "-------------------------------- PLAY WITH WORDS ---------------------------------" << endl;
		
		while(choice != 4)
		{
			cout << "\n\n";
			cout << "\t\t\t\t\t\t\t1. Word Suggestion " << endl;
			cout << "\t\t\t\t\t\t\t2. Unscramble " << endl;
			cout << "\t\t\t\t\t\t\t3. Delete " << endl;
			cout << "\t\t\t\t\t\t\t4. Quit " << endl;
			
			cout << "\n\t\t\t\tEnter your choice: ";
			cin >> choice;
			
			switch(choice)
			{
				case 1:
					cout << "\n\n------------------------ SUGGESTIONS for WORD COMPLETION -------------------------\n" << endl;
					char phrase[20];
					cout << "\nEnter beginning letters of a word:  ";
					cin >> phrase;
					cout << "\nSUGGESTIONS:\n";
					traverseTrie(phrase);
					cout << "\n\n------------------------------------ MENU ----------------------------------------" << endl;
					break;
					
				case 2:
					unscramble++;
					cout << "\n\n-------------------------- UNSCRAMBLE the SCRAMBLED ------------------------------\n" << endl;
					cout << "\nEnter the letters to be unscrambled: ";
					cin >> phrase;
					cout << "\nHow many ways do you think '" << phrase << "' can be rearranged to get a meaningful word ?" << endl << endl;
					print_all_permutations(phrase);
					if(countArray[unscramble] == 0)
						cout<<"\nNo ways!\n"<<endl;
					else
						cout << '\n' << countArray[unscramble] << " ways" << endl;
					cout << "\n\n------------------------------------ MENU ----------------------------------------" << endl;
					break;
					
				case 3:
					cout << "\n\n--------------------------DELETE A WORD------------------------------\n" << endl;
					cout << "\nEnter the word to be deleted: ";
					cin >> phrase;
					removeWord(phrase);
					break;
					
				default:
					cout << "\n\t\t\t\tInvalid Entry!" << endl;
			}
		}
	}
	
	return 0;
}
