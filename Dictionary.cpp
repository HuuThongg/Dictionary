#include "AnagramSet.h"
#include "Dictionary.h"
#include "LetterBag.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


Dictionary::Dictionary(){

    numWords = 0;
}


Dictionary::Dictionary(string fileName){

    ifstream fin;

    fin.open(fileName);

    string temp;

    numWords = 0;

    if (!fin.is_open())

        return;

    while (fin >> temp)

        insertWord(temp);
}

// insert all words from the array into an empty dictionary.
Dictionary::Dictionary(string words[], int arraySize)
{
    numWords = 0;

    for (int i = 0; i < arraySize; i++)

        insertWord(words[i]);

}
// copy constructor
Dictionary::Dictionary(const Dictionary &d){

    clear();
    if(d.getNumWords() == 0)

        return;

    for(int i = 0; i < tableSize; i++){

        if(d.hashTable[i] == nullptr)

            hashTable[i] = nullptr;
        else{

            AnagramSet *headPointer = new AnagramSet(d.hashTable[i]->key);

            AnagramSet * dCurrent = d.hashTable[i]->next;

            AnagramSet * thisPre = headPointer;

            vector<string> temp1 = d.hashTable[i]->getWords();

                for(int j = 0; j < temp1.size(); j++)

                    thisPre->insert(temp1[j]);

            while(dCurrent != nullptr){

                thisPre->next = new AnagramSet(dCurrent->key);

                vector<string> temp = dCurrent->getWords();

                for(int k = 0; k < temp.size(); k++)

                    thisPre->next->insert(temp[k]);

                dCurrent = dCurrent->next;

                thisPre = thisPre->next;
            }

            hashTable[i] = headPointer;

            thisPre->next = nullptr;
        }


    }
    numWords = d.numWords;
}

Dictionary::~Dictionary(){

    clear();

}

int Dictionary::getNumWords() const{

    return numWords;

}


// remove all the words.
void Dictionary::clear()
{
    for (int i = 0; i < tableSize; i++)
    {
        AnagramSet *headPointer = hashTable[i];

        while (headPointer != nullptr)
        {
            AnagramSet *previous = headPointer;

            headPointer = headPointer->next;

            delete previous;
        }

    }

    numWords = 0;
}


bool Dictionary::insertWord(const string &w){

    LetterBag A(w);

    int index = A.hashValue(tableSize);

    if (hashTable[index] == nullptr){

        hashTable[index] = new AnagramSet(LetterBag(w));

        hashTable[index]->insert(w);

        numWords++;

        return true;
    }
    else{
        // one anagramSet
        AnagramSet *current = hashTable[index]->next;

        AnagramSet *prevPointer = hashTable[index];

        while (current != nullptr){

                LetterBag B = prevPointer->key;

                if (B == A){

                    if(!prevPointer->contains(w)){

                        prevPointer->insert(w);

                    numWords++;

                    }

                    return true;
                }
                else{

                    prevPointer = current;

                    current = current->next;
                }
            }

        LetterBag B = prevPointer->key;

            if (B == A){

                if(!prevPointer->contains(w)){

                    prevPointer->insert(w);

                numWords++;

                }

                return true;
            }

        AnagramSet *newAna = new AnagramSet(LetterBag(w));

        newAna->next  = hashTable[index];

        newAna->insert(w);

        hashTable[index] = newAna;

        numWords++;

        return true;
    }
    return false;

}

// insert multiple words and return how many weren’t already there.
int Dictionary::insertWords(vector<string> v)
{
    for (vector<string>::iterator i = v.begin(); i != v.end(); i++)

        insertWord(*i);

    return v.size();
}


// remove the word. Return true if it was there to be removed and false otherwise.
bool Dictionary::removeWord(string w){

    LetterBag temp(w);

    int index = temp.hashValue(tableSize);

    AnagramSet *headPointer = hashTable[index];

    if (headPointer == nullptr)

        return false;

     AnagramSet *current = headPointer->next;

    if(headPointer->key == temp){

        if (headPointer->contains(w)){

            headPointer->remove(w);

            numWords--;

            if (headPointer->getSize() == 0){

                hashTable[index] = current;

                delete headPointer;
            }
             return true;
        }
        else
            return false;

    }
    while( current != nullptr && current->key != temp  ){

        headPointer = current;

        current = current->next;
    }

    if ( current != nullptr && current->contains(w)){

        current->remove(w);

        numWords--;

        if (current->getSize() == 0){

            headPointer->next = current->next;

            delete current;
        }

        return true;
    }

    return false;
}
bool Dictionary::contains(string word) const
{

    LetterBag temp(word);

    int index = temp.hashValue(tableSize);

    AnagramSet *headPointer = hashTable[index];

    if (headPointer == nullptr)
        return false;

    while (headPointer != nullptr && headPointer->key != temp   )

        headPointer = headPointer->next;


    if ( headPointer != nullptr && headPointer->contains(word) )

        return true;

    return false;
}

// return words that are anagrams for the given word.
vector<string> Dictionary::getWords(const string &word) const
{
    LetterBag temp(word);

    int index = temp.hashValue(tableSize);

    AnagramSet *headPointer = hashTable[index];

    while ( headPointer != nullptr  &&headPointer->key != temp)

        headPointer = headPointer->next;

    if(headPointer == nullptr){

        vector<string> a;

        return a;
    }

    return headPointer->getWords();
}
// return number of anagrammatic forms found for the given word.
int Dictionary::getNumAnagrams(const string &word) const
{

    string w = word;

    LetterBag A(w);

    int index = A.hashValue(tableSize);

    AnagramSet *current = hashTable[index]->next;

        AnagramSet *prevPointer = hashTable[index];

        while (current != nullptr){

                LetterBag B = prevPointer->key;

                if (B == A){

                    return prevPointer->getSize();
                }
                else{

                    prevPointer = current;

                    current = current->next;
                }
            }
        LetterBag B = prevPointer->key;

            if (B == A){
                return prevPointer->getSize();
            }
    return 0;


}

void Dictionary::printDictionary(int limit, ostream &out) const
{
    int i = 0, count = 0;

    while(count < limit && i < tableSize){

        while(hashTable[i] == nullptr && i < tableSize){
            i++;
        }
        if(i < tableSize){

            AnagramSet *headPointer = hashTable[i];

            out << setw(5) << i << "...\t";

            while (headPointer != nullptr){

                    out << *headPointer << "  ";

                headPointer = headPointer->next;
            }

            out << endl;

            i++;

            count++;

        }
    }

}

