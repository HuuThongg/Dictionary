
#include "AnagramSet.h"
#include <iostream>
#include <vector>

using namespace std;
ostream &operator<<(ostream &out, const AnagramSet &s){
        out << "{" << s.key << ": ";
        for(int i = 0; i < s.words.size(); i++){
            out << s.words[i];
            if(i < s.words.size() - 1)
                out <<", ";
        }
        out << " }";

    return out;
}
AnagramSet::AnagramSet(const LetterBag &theKey) : key(theKey){
    next = nullptr;
}

void AnagramSet::insert(const string &s){
    // ate atf eat eta    s = tea   s = ebc s = aet
    if(contains(s)) return;
    vector<string>::const_iterator index = words.begin();
    for( int i = 0 ; i < this->getSize(); i++){
        if(words[i] > s)
            break;
        index++;
    }
    words.insert(index, s);
}


// Return the number of words, i.e. size of the words vector.
int AnagramSet::getSize() const{
    return words.size();
}

// Return true iff s is in the words vector and false otherwise
bool AnagramSet::contains(const string &s){
    for (int i = 0; i < words.size(); i++){
        //if( words[i] == s)
        if(s.compare(words[i]) == 0)
            return true;
    }
    return false;
}

// Remove all the words i.e. set words to the empty vector.
void AnagramSet::clear(){
    for (int i = 0; i < words.size(); i++)
        words[i] = "";
}

// Remove s from the set of words. If it's there then do nothing.
void AnagramSet::remove(const string &s){
    int i;
    for(i = 0; i < words.size(); i++){
        if(words[i] == s)
            break;
    }
    words.erase(words.begin() + i);
}

// Return the vector of words.

vector<string> AnagramSet::getWords() const{
    return words;
}
