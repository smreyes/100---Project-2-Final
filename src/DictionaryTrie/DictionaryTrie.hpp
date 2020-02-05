#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

class TNode {
	public:
		const char symbol;
		bool isWord;
		unsigned int freq;
		TNode* left;
		TNode* middle;
		TNode* right;
		TNode* parent;

		TNode(const char c, bool b, const unsigned int f);
};

class DictionaryTrie {

	public:
	
	DictionaryTrie();

	bool insert(string word, unsigned int freq);

	bool find(string word) const;

	vector<string> predictCompletions(string prefix, unsigned int numCompletions);
	vector<string> predictUnderscores(string pattern, unsigned int numCompletions); 
    
    	/* Destructor */
    	~DictionaryTrie();

	private:


	TNode* root;

	void deleteAll(TNode* root) const;

	void predictHelper(TNode* n, string s, list<pair<string, unsigned int>> &  allWords) const;
	//void searchHelper(string& prefix, TNode* n);
	
	void underscoreHelper(TNode* n, int len, string s, list<pair<string, unsigned int>> &possibles) const;

};
/*
class comparison {
	public:

		bool operator()(pair<string, unsigned int>& a, pair<string, unsigned int> &b) const {
			if (a.second > b.second)
         			return true;
      			if (a.second < b.second)
         			return false;
      			return a.first < b.first;
	 		return std::tie(b.second, a.first) < std::tie(a.second,a.first);
		}

};*/	
#endif


