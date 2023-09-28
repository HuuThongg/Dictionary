#ifndef ANAGRAMSET_H
#define ANAGRAMSET_H

#include <vector>
#include <iostream>
#include "LetterBag.h"

using namespace std;

class AnagramSet : public LetterBag
{
    friend ostream &operator<<(ostream &out, const AnagramSet &s);
    // Output the AnagramSet in format {aet: ate, eat, eta, tea}
    // aet is the key as a sorted string and ate, eat ... are the words.
    private:
        vector<string> words;
        // Member functions
    public:
        AnagramSet *next;
        const LetterBag key;

        AnagramSet(const LetterBag &theKey); // Initialize key using constructor initialization list : key(theKey)

        void insert(const string &s); // Insert a new word in sorted oDrder. Don't insert if it's already there.

        void remove(const string &s); // Remove s from the set of words. If it's there then do nothing.

        int getSize() const; // Return the number of words, i.e. size of the words vector.

        bool contains(const string &s); // Return true iff s is in the words vector and false otherwise

        void clear(); // Remove all the words i.e. set words to the empty vector.

        vector<string> getWords() const; // Return the vector of words.

        // We won't need a getKey function, since key is a public constant.
};

#endif
