#include <iostream>       // input output 
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::second
#include <fstream>        // for reading from dictionary file

// checklist :
// 1. words are getting appended at the end of the dictionary
// 2. able to read all the words from the dictionary



// things that could go wrong

// 1. the scope of freeopen may go out of the function,so used fstream
// 2. some function in the switch may not be implemented properly
// 3. Some typo error

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

    void insert(std::string);
    bool search(std::string);
    int printAutoSuggestions(const std::string);
    void dfs(TrieNode*, std::string);
};

// searching for any word
void searchForWord(Tries* obj) {
    std::string word;

    std::cout << "Enter your word:\n";
    std::cin >> word;

    // printing all the matching words
    obj->printAutoSuggestions(word);
}


// adding a new word
void addNewWord(Tries* obj) {

    //extra features : check for memory overflow (yet to be implemented)

    std::string word;

    std::cout << "Input your word to add :\n";
    std::cin >> word;
    // see if already present
    if(!obj->search(word)) {
        obj->insert(word);

        //adding to the dictionary
        std::ofstream cout("dictionary.txt", std::ios::app);
        std::cout << word;
    }
    else {
        std::cout << "Already present\n";
    }
}

// printing choices
void printChoices() {
    std::cout << "What is your mood now?\n";
    std::cout << "1. Add a new word to the dictionary\n";
    std::cout << "2. Search for a word match (lower case)\n";
    std::cout << "3. Clear entire search history (experimental)\n";
    std::cout << "4. Exit\n";
}

// a way to clear screen or basically shift it up
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// reading the dictionary and building up the Trie
void buildTrie(Tries *obj) {
    // freopen("dictionary.txt", "r", stdin);
    // since freopen redirects the stdin to file
    std::ifstream cin("dictionary.txt");

    std::string word;

    // input each word
    while(std::cin >> word) {
        // inserting each word
        obj->insert(word);
    }
}

// print the welcome message
void welcomeMessage() {
    std::cout << "Welcome to Treacher, an advanced searching tool based on Tries\n";
    std::cout << "Version : 1.0\nDeveloper : Vivek Dubey\n\n\n";
    std::cout << "Processing the dictionary\n\n";
}

int main() {
    int choiceOperation;
    bool statusOfT = true;

    welcomeMessage();
    Tries *newTrie = new Tries;
    buildTrie(newTrie);
    std::this_thread::sleep_for (std::chrono::seconds(2));
    // start 
    while(statusOfT) {
        clearScreen();
        printChoices();
        std::cin >> choiceOperation;
        switch(choiceOperation) {
            case 1: addNewWord(newTrie);
                break;
            case 2: searchForWord(newTrie);
                break;
            case 3: std::cout << "Under progress\n";
                break;
            case 4:
                statusOfT = false;
                break;
                
            default: std::cout << "Wrong choice!\n";
        }
    }

    return 0;
}

// Implementation details of Tries functions

void Tries::insert(std::string word) {
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
bool Tries::search(std::string word) {
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
void Tries::dfs(TrieNode* curr, std::string currPrefix) { 
	// found a match
	if (curr->isWordEnd) { 
		std::cout << currPrefix << "\n"; 
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
int Tries::printAutoSuggestions(const std::string query) { 
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
		std::cout << query << "\n"; 
		return 1; 
	}

	// if ther are more matchings
	if (!isLast) 
	{ 
		std::string matches = query; 
		dfs(parent, matches); 
		return 2; 
	} 
    return 2;
} 
