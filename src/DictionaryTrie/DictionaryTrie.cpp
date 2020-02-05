/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <list>
#include <string>
#include <vector>

using namespace std;

TNode::TNode(const char c, bool b, const unsigned int f) : symbol(c), isWord(b), freq(f), left(0), middle(0), right(0), parent(0) {}

/* TODO */
DictionaryTrie::DictionaryTrie():root(0){}

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
	if (word.empty()){
			return false;
	}
	//TNode* curr = root;
	
	//check if tree is empty
	if (root == NULL) {
		//if word only has one char
		if (word.length() == 1){
			root = new TNode (word[0], true, freq);
			return true;
		}
		//if word contains more than 1 char, initilize the root to contain the first char of the string
		else {
			root = new TNode(word[0], false, 0);
		}
	}

	TNode* curr = root;
	//insert each symbol in correct position
	for (unsigned int i = 0; i < word.length();) {
		//check if current node = current char of the string
		if (curr->symbol == word[i]) {

			if (curr->middle != NULL) {
				//if at the end of the work already
				if (i == word.length()-1) {
					if(curr->isWord == false) {
						curr->isWord = true;
						curr->freq = freq;
						return true;
					}
					// word is a duplicate
					else{
						return false;
					}
				}
				else {
					curr = curr->middle;
					i++;
					continue;
				}
			}

			else if (curr->middle == NULL) {
				if(i!=word.length() - 1){
					bool b = (i == (word.length() -2));
					curr->middle = new TNode(word[i+1], b, b?freq:0);
					curr=curr->middle;
					i++;
					if (b) {
					       	return true;
					}
				}
				else if (curr->isWord == false) {
					curr->isWord = true;
					curr->freq = freq;
					return true;
				}
				
				//word trying to insert is a duplicate
				else{
				       	return false;
				}
			}
		}
		//if current symbol of word we're inserting is greater than the current node pointed at
		//traverse to the right	
		else if(word[i] > curr->symbol) {
			//if there's a node to the right
			if (curr->right != NULL) {
				curr=curr->right;
				continue;
			}
			//if right child is NULL
			else {
				bool b = (i == (word.length()-1));
				curr->right = new TNode(word[i], b, b?freq:0);
			        curr = curr->right;
		        	if (b) {
		       			return true;
				}
			}
		}
		//current symbol of word is less than the current node 
		//traverse to the left
		else {
			if (curr->left != NULL) {
				curr = curr->left;
				continue;
			}
			//left child is NULL
			else {
				bool b = (i == (word.length()-1));
				curr->left = new TNode(word[i], b, b?freq:0);
				curr = curr->left;
				if (b) {
					return true;
				}
			}
		}			
	}
	return false;
}	

/* TODO */
bool DictionaryTrie::find(string word) const {

	TNode* curr = root;

	if(word.length() == 0)
		return false;

	for (unsigned int i = 0; i < word.length();) {
		if (curr != NULL) {
			if(curr->symbol == word[i]) {
				i++;
				if(i==word.length()) {
					if(curr->isWord == true)
						return true;
					else
						return false;
				}
				//if not the end of string
				curr = curr->middle;
			}
			//check the right subtree
			else if (word[i] > curr->symbol) {
				curr = curr->right;
			}
			//check left subtree
			else 
				curr = curr->right;
		}
		//pointed to an empty child, hence word not found
		else 
			return false;
	}
	return false;
}
/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix, unsigned int numCompletions) {
    	vector<string> completions;

    	list<pair<string, unsigned int>> allWords;
    
    	if (numCompletions == 0 || prefix == ""){
	   	return completions;
	}
	
	TNode* curr = root;

	//go to the last char of the prefix
	for (unsigned int i = 0; i < prefix.length();) {
		if (curr != NULL) {
			if (curr->symbol == prefix[i]) {
				i++;
				if (i==prefix.length())
					break;
				curr = curr->middle;
			}
			
			else if (prefix[i] < curr->symbol) 
				curr=curr->left;
			else
				curr=curr->right;
		}
		//prefix is not in trie
		else 
			return completions;	
	}

	if (curr != NULL){

		if (curr->isWord) {
			allWords.push_back(make_pair(prefix, curr->freq));
		}
	}
	else {
		return completions;
	}

	predictHelper (curr->middle, prefix, allWords);

	//sort list of pairs based on second element, then for ties, sort based on first element
	allWords.sort([](auto const& a, auto const& b) {
			
		if (a.second > b.second)
         		return true;
      		if (a.second < b.second)
         		return false;
      		return a.first < b.first;
		//return tie(b.second, a.first) < tie(a.second, a.first);
	});
	
	for(auto const& p: allWords) {
		if (completions.size() < numCompletions)
			completions.push_back(p.first);
		else
			break;
	}
	return completions;
}

void DictionaryTrie::predictHelper(TNode* n, string s, list<pair<string, unsigned int>> & allWords)const {

	if (n==NULL) return;

	else {
		string temp = s + n->symbol;

		//check if node is a valid word
		if (n->isWord == true) 
			allWords.push_back(make_pair(temp, n->freq));
	
	predictHelper(n->middle, temp, allWords);
	predictHelper(n->left, s, allWords);
	predictHelper(n->right, s, allWords);
	}
	return;
}

/* TODO */
vector<string> DictionaryTrie::predictUnderscores(string pattern, unsigned int numCompletions) {
	vector<string> completions;
	list<pair<string,unsigned int>> possibles;

	TNode* curr = root;

		
} 


/* TODO */
DictionaryTrie::~DictionaryTrie() {
	deleteAll(root);
}

void DictionaryTrie::deleteAll(TNode* n) const {

	if(!n) return;

	else {
		deleteAll(n->left);
		deleteAll(n->middle);
		deleteAll(n->right);
		delete n;
		return;
	}
}
