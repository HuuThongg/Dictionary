/*
#include "Dictionary.h"

#include <iostream>

using namespace std;

void printWords(vector<string> v) {

    for (int i = 0; i < v.size(); i++)

        cout << v[i] << " ";

    cout << endl;

}

int main() {

    char response;

    string fileName;

    cout << "Enter the file name: ";

    cin >> fileName;

    Dictionary d(fileName);

    cout << "Here is the dictionary..." << endl;

    d.printDictionary();
    cout << "Number of words = " << d.getNumWords() << "\ttableSize = " << d.tableSize << endl;
    bool done = false;

    while (!done) {

        string s;

        cout << "Enter an anagram: ";

        cin >> s;



        vector<string> v = d.getWords(s);

        if (v.empty())

            cout << "No matches..." << endl;

        else {

            cout << "Matching words are: ";

            printWords(v);

        }

        cout << "Enter a list of words to insert followed by 'q': ";

        do {

            cin >> s;

            if (s != "q") d.insertWord(s);

        } while (s != "q");

        cout << "The words were inserted. " << endl;

        cout << "Enter a list of words to remove followed by 'q': ";

        do {

            cin >> s;

            if (s != "q") d.removeWord(s);

        } while (s != "q");

        cout << "The words were removed. " << endl;

        cout << "The new dictionary is..." << endl;

        d.printDictionary();
        cout << "Number of words = " << d.getNumWords() << "\ttableSize = " << d.tableSize << endl;

        cout << "Continue? ";

        cin >> response;

        if (response != 'y') done = true;

    }

    cout << "Bye!" << endl;

    Dictionary m = d;
    m.printDictionary();
    return 0;

}
*/


#include <iostream>
#include "AnagramSet.h"
#include "Dictionary.h"
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
const int maxWords = 200000;
string words[maxWords], reversedWords[maxWords];

int tfine; // used for timer

void resetTimer() ;  // reset the timer
int getTime();  // get elapsed time

// read file into wordList. Return number of words read in
int readInWords(string wordList[],  int maxSize, string fileName) ;

// return the reverse of s
string reverse(const string & s);

// count the number of words in wordList that are in d
void countHits (string wordList[], int length,  const Dictionary & d);

// write the dictionary to a file
void toFile(const Dictionary & d, const string & fileName) ;

// find palindromic words (bob) and palindrom pairs (live evil)
void findMirrorAnagrams(const Dictionary & d, int wordCount);

// count anagrams
void countWordsWithNAnagrams(const  Dictionary & d, int N, string wordList[], int length);

// remove words from dictionary
void removalTest( Dictionary & d, int wordCount, int howMany) ;

// insert words to dictionary
void insertionTest( Dictionary & d, int wordCount);

// find words whose letters match a given string
void unScramble(const Dictionary & d);

int main() {


	cout << "Press any key to start tests.";
	cin.get();
	int  tableSize = Dictionary::tableSize;

	resetTimer();

	cout << "Starting" << endl;
	int wordCount = readInWords(words, maxWords,"words.txt");

	cout << "Read in " << wordCount << " words " << endl;
	cout << "Done reading words, elapsed time = " << getTime() << endl << endl;

	resetTimer();
	static Dictionary d(words, wordCount);


	cout << "Done creating dictionary, elapsed time = " << getTime() << endl;
	cout << "The first 30 nonempty buckets of the dictionary are printed below." << endl;

	d.printDictionary(30);

	countHits(words,wordCount,d);

	resetTimer();

	toFile(d, "full.txt");
	cout << "Done writing to file, elapsed time = " << getTime() << endl;
	cout << "Press any key to continue tests...";
	cin.get();

	findMirrorAnagrams(d,wordCount);

	for (int i = 1; i <= 13; i++)
		countWordsWithNAnagrams(d,i,words,wordCount);
    cout << "--------------------------" << endl;
	removalTest(d, wordCount, wordCount-100);

	removalTest(d, wordCount, wordCount);  // remove all the words from what's left

	insertionTest(d, wordCount); // insert words back into the dictionary
	insertionTest(d, wordCount); // redundantly insert words that are already there

	unScramble(d);
	cout << "Press any key to exit." << endl;
	cin.get(); cin.get();

	return 0;
}


void resetTimer() {
	tfine = clock();
}

int getTime() {
	return clock() - tfine;
}

int readInWords(string wordList[],  int maxSize, string fileName) {
    int i = 0;
	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile) cout <<"Failed to open file" << endl;
    while (infile && i < maxSize) {
        string s;
        infile >> s;
        if (infile) {
            wordList[i] = s;
            i++;
        }
    }
    return i;  // the number of words read in
}

void countHits (string wordList[], int length,  const Dictionary & d) {
	resetTimer();
	int count = 0;
	for (int i = 0; i < length; i++)
		if (d.contains(wordList[i]) )
			count++;

	cout << "Hit count = " << count
		<< ",  elapsed time = " << getTime() << "." << endl << endl;
}

string reverse(const string & s) {
	string t;
	for (int i = s.length()-1; i >= 0; i--)
		t.push_back(s[i]);
	return t;
}

void toFile(const Dictionary & d, const string & fileName) {
	ofstream out;
	out.open(fileName.c_str());
	cout << "Opened file " << fileName << "." << endl;
	d.printDictionary(Dictionary::tableSize, out);  // first argument is maximum number of buckets to output
	cout << "===================================" << endl;
	out.close();
}

// From a given wordList count the number of words that have n anagramatic forms.
// There's a faster way of counting if we know d contains the same words
// as wordList, but for the sake of testing we'll ignore that fact.
void countWordsWithNAnagrams( const Dictionary & d, int n, string wordList[], int length) {
	resetTimer();
	int sum = 0;
	for (int i = 0; i < length; i++)  {
		if (d.getNumAnagrams(wordList[i]) == n)
			sum++;
	}
	cout	<< "Found " << setw(7) << sum
			<< " words with  " << setw(5) << n << " anagramatic form" << (n == 1 ? ". " : "s.") << " Elapsed time = "
			<< getTime() << "." << endl;
}
// We'll call a mirror anagram a word for which the reverse of the word is also a word
void findMirrorAnagrams(const Dictionary & d, int wordCount) {
	static Dictionary pal;
	pal.clear();
	cout << "Creating reversed word list...";
	for (int i = 0; i < wordCount; i++)
		reversedWords[i] = reverse(words[i]);
	cout << endl << "Counting mirror words.";
	countHits(reversedWords, wordCount, d);
	cout <<  "Creating mirror words dictionary...";
	for (int i = 0; i < wordCount; i++)  {
		if (d.contains(reversedWords[i])) {
			pal.insertWord(words[i]);
			pal.insertWord(reversedWords[i]);
		}
	}
	cout << "done.  " << endl;
	toFile(pal, "symmetric.txt");

	cout << "Writing to file. " << endl << endl;
}

void removalTest( Dictionary & d, int wordCount, int howMany) {
	resetTimer();
	int removalCount = 0;
	for (int i = 0, j = 0; j < howMany; i = (i + 22079) % wordCount, j++)
		if (d.removeWord(words[i])) removalCount++;
	cout << endl << "Done removing " << removalCount << " words, elapsed time = " << getTime() << "." << endl << endl;
	cout << "All nonempty buckets of current dictionary are printed below. " << endl;
	d.printDictionary();
	countHits(words,wordCount,d);
}


void insertionTest( Dictionary & d, int wordCount) {
	int insertionCount = 0;
	resetTimer();
	for (int i = wordCount - 1; i >= 0; i--)
		if (d.insertWord(words[i])) insertionCount++;
	cout << "Done inserting " << insertionCount << " words, elapsed time = " << getTime() << "." << endl << endl;
	countHits(words,wordCount,d);

}


void unScramble(const Dictionary & d) {
	string s;
	do {
		cout << "Enter an anagram or q to quit: ";
		cin >> s;
		if (s != "q") {
				vector<string> v = d.getWords(s);
				if (v.empty())
					cout << "Not found. " << endl;
				else
					for (int i = 0; i < v.size(); i++) cout << v[i] << " ";

				cout << endl;

		}
	} while (s != "q");
}


