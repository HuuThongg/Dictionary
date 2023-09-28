
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <iostream>
#include "AnagramSet.h"
#include "LetterBag.h"

#include <fstream>

using namespace std;
class Dictionary
{
public:
    static const int tableSize = 5001; // this will change for different tests. 200001 5001
private:
    AnagramSet *hashTable[tableSize] = {nullptr}; // an array of AnagramSet chains.

    int numWords; // number of words currently in the dictionary.

    // OPTIONAL HELPER FUNCTIONS ARE INCLUDED BELOW. YOU CAN OMIT ANY OR ALL OF THESE IF YOU WANT.

    // return pointer to the node containing key or return null if not found.

    // AnagramSet *findKey(AnagramSet *head, const LetterBag &key);

    // Return pointer to the node before the node containing key.

    // If key is int head node then return nullptr.

    // If key is not found, return point to last node in chain.

    // AnagramSet *findPrevious(AnagramSet *head, const LetterBag &key);

    // insert a new AnagramSet at the beginning of the chain.

    // void insertNew(int index, AnagramSet *toInsert);

public:


    Dictionary(); // default constructor: creates an empty dictionary.

    Dictionary(string fileName); // insert all words from the file into an empty dictionary.

    Dictionary(string words[], int arraySize); // insert all words from the array into an empty dictionary.

    Dictionary(const Dictionary &d); // copy constructor

    ~Dictionary(); // destructor

    int getNumWords() const; // return number of words.

    void clear(); // remove all the words.

    bool insertWord(const string &w); // insert a word, return true if wasn’t already there, false if already there.

    int insertWords( vector<string> v); // insert multiple words and return how many weren’t already there.

    bool removeWord(string w); // remove the word. Return true if it was there to be removed and false otherwise.

    bool contains(string word) const;

    vector<string> getWords(const string &word) const; // return words that are anagrams for the given word.

    int getNumAnagrams(const string &word) const; // return number of anagrammatic forms found for the given word.

    // Print AnagramSets in each bucket of table.

    // That just means loop through the array and whenever a bucket isn't empty (not null)

    // loop through the linked list and call operator<< on each AnagramSet object. Do not output an endl until

    // all AnagramSet objects in that bucke have been output.  (See sample output above.)

    // If limit is less than tableSize then only print out result for the first limit nonempty buckets.

    // For example if limit were 2, we would stop after AnagramSets in the second nonempty bucket were output.

    void printDictionary(int limit = tableSize, ostream &out = cout) const;
};
#endif
