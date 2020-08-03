#include<iostream> 
using namespace std; 

// considering only lowercase letters
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd; 
}; 

class Tries {
    TrieNode *root;

    // helper functions

    // create a new node
    TrieNode* makeNode() {
        TrieNode *newNode = new TrieNode;
        newNode->isWordEnd = false;
        for(int i = 0; i < 26; i++)
            newNode->children[i] = NULL;
        return newNode;
    }

    // check if the current node is the last node
    bool isLastNode(TrieNode* curr) { 
        for (int i = 0; i < ALPHABET_SIZE; i++) 
            if (curr->children[i]) 
                return false; 
        return true; 
    } 

    public:
    
    // constructor
    Tries() {
        root = makeNode();
    }

    void insert(string);
    bool search(string);
    int printAutoSuggestions(const string);
    void dfs(TrieNode*, string);
};


// Driver Code 
int main() 
{ 
	Tries *newTrie = new Tries;

	newTrie->insert("diamond"); 
	newTrie->insert("district"); 
	newTrie->insert("dibora"); 
	newTrie->insert("hiii"); 
	newTrie->insert("how"); 
	newTrie->insert("home"); 
	newTrie->insert("damage"); 
	newTrie->insert("dose"); 
	newTrie->insert("distance"); 
	int comp = newTrie->printAutoSuggestions("di");

	if (comp == -1) 
		cout << "No other strings found with this prefix\n"; 

	else if (comp == 0) 
		cout << "No string found with this prefix\n"; 

	return 0; 
} 

void Tries::insert(string word) {
    TrieNode *parent = root;

    //traverse the Trie and create nodes if not present
    for(int i = 0; i < word.size(); i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if(!parent->children[index]) {
            parent->children[index] = makeNode();
        }
        parent = parent->children[index];
    }

    // mark last node as end of word
    parent->isWordEnd = true;
}

// search for an exact match
bool Tries::search(string word) {
    TrieNode *parent = root;

    // Traverse the Trie and return false if current node doesnt exists
    for(int i = 0; i < word.size(); i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if(!parent->children[index]) {
            return false;
        }
        parent = parent->children[index];
    }

    // last should not be null and also should be end of the word
    return (parent != NULL && parent->isWordEnd);
}

// search for all possible matches
void Tries::dfs(TrieNode* curr, string currPrefix) { 
	// found a match
	if (curr->isWordEnd) { 
		std::cout << currPrefix; 
		std::cout << endl; 
	} 

	// leaf node
	if (isLastNode(curr)) {
        return; 
    }		

	for (int i = 0; i < ALPHABET_SIZE; i++) { 
		if (curr->children[i]) { 
			// append the current character
			currPrefix.push_back(97 + i); 
			// dfs for the new formed string
            dfs(curr->children[i], currPrefix); 
			// remove the last added character 
            // for dfs over other nodes
			currPrefix.pop_back(); 
		} 
	} 
} 

// print suggestions for given query prefix. 
int Tries::printAutoSuggestions(const string query) { 
	struct TrieNode* parent = root; 

	// traverse Trie and find the last node 
    // corresponding to the last character of the query
	for (int i = 0; i < query.size(); i++) { 
		int index = CHAR_TO_INDEX(query[i]); 
		// no match found
		if (!parent->children[index]) 
			return 0;
		parent = parent->children[index]; 
	} 

	// given word is present
	bool isWord = (parent->isWordEnd == true); 

	// is last node of the Trie
	bool isLast = isLastNode(parent); 

	// If query present as a word in the dictionary, but 
	// there is no other matchings
	if (isWord && isLast) {
		std::cout << query << endl; 
		return 1; 
	}

	// if ther are more matchings
	if (!isLast) 
	{ 
		string matches = query; 
		dfs(parent, matches); 
		return 2; 
	} 
    return 2;
} 
