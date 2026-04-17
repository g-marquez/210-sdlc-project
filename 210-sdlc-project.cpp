//*****************************************************************************
// COMSC-210 | Lab 31 | Gabriel Marquez
// Description: this file shows the deployment and maintainance stage for the
// language evolution simulation SDLC project.
//*****************************************************************************

//Include necessary headers for file handling, data structures, etc.
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <fstream>
#include <random>
#include <sstream> //for parsing data from corpus.txt
#include <algorithm> //for any_of
using namespace std;

//declare global variables
const int GENERATIONS = 25;
const int FORMAL = 0;
const int CASUAL, LIST_MIN = 1;
const int SLANG  = 2;
const int ARR_SIZE = 3;

//declare function prototype(s) for different language changes
string new_slang(string);
void print_corpus(map<string, array<list<string>, ARR_SIZE>>);

//define main function
int main() {
    //srand for random chances later on in simulation
    srand(time(0));

    //initialize data structures to store language concepts
    map<string, array<list<string>, ARR_SIZE>> corpus;
    array<list<string>, ARR_SIZE> words;
    list<string> formal, casual, slang;

    //read data from file and populate map
    ifstream fin ("corpus.txt");
    if (!fin.good()) {
        cout << "ERROR! Please verify file name and directory and restart program.";
        return 1;
    }
    else {
        //extract concept and word data
        string concept, formalLine, casualLine, slangLine;
        while (getline(fin, concept)) {
            getline(fin, formalLine);
            getline(fin, casualLine);
            getline(fin, slangLine);

            //parse and add words in each line into list
            //formal list
            stringstream ss1(formalLine);
            string word1;
            while (getline(ss1, word1, ',')) {
                formal.push_back(word1);
            }

            //casual list
            stringstream ss2(casualLine);
            string word2;
            while (getline(ss2, word2, ',')) {
                casual.push_back(word2);
            }

            //slang list
            stringstream ss3(slangLine);
            string word3;
            while (getline(ss3, word3, ',')) {
                slang.push_back(word3);
            }

            words = {formal, casual, slang};
            corpus.insert(make_pair(concept, words));

            //clear lists for next iteration
            formal.clear();
            casual.clear();
            slang.clear();
        }
        //close file
        fin.close();
    }

    //print corpus before simulation
    cout << "Original corpus: " << endl;
    print_corpus(corpus);
    cout << endl << "Beginning simulation..." << endl;
    
    //begin language evolution simulation
    //for 25 time intervals (generations)
    for (int i = 0; i < GENERATIONS; ++i) {
        for (auto &c : corpus) {
            auto &lists = c.second;
            list<string> &formal = lists[FORMAL];
            list<string> &casual = lists[CASUAL];
            list<string> &slang  = lists[SLANG];
            
            //chance for word to move from slang->casual or casual->formal
            //lowered to 40%
            int prob1 = rand() % 100 + 1;
            if (prob1 <= 40) {
                if ((rand() % 100) < 60) {
                    //slang->casual
                    if (slang.size() > LIST_MIN) {
                        //choose random word from that list
                        int word_index = rand() % slang.size();
                        auto it = slang.begin();
                        //advance to that word in the list and move it
                        advance(it, word_index);
                        casual.push_back(*it);
                        slang.erase(it);
                    }
                }
                else {
                    //casual->formal
                    if (casual.size() > LIST_MIN) {
                        //choose random word from that list
                        int word_index = rand() % casual.size();
                        auto it = casual.begin();
                        //advance to that word in the list and move it
                        advance(it, word_index);
                        formal.push_back(*it);
                        casual.erase(it);
                    } 
                }
            }

            //chance for word to die
            //lowered to 10%
            int prob2 = rand() % 100 + 1;
            if (prob2 <= 10) {
                //randomly select one of the 3 lists to erase from
                int list_index = rand() % 3;
                if (lists[list_index].size() > LIST_MIN) {
                    //choose random word from that list
                    int word_index = rand() % lists[list_index].size();
                    auto it = lists[list_index].begin();
                    //advance to that word in the list and delete it
                    advance(it, word_index);
                    lists[list_index].erase(it);
                }
            }

            //chance for new slang to be created
            int prob3 = rand() % 100 + 1;
            if (prob3 <= 50) {
                //randomly choose the formal or casual list
                int list_index = rand() % 2;
                if (lists[list_index].size() > LIST_MIN) {
                    //choose random word from that list
                    int word_index = rand() % lists[list_index].size();
                    auto it = lists[list_index].begin();
                    //advance to that word in the list
                    advance(it, word_index);
                    string new_word = new_slang(*it);
                    //check if the new word already exists in the list
                    bool hasWord = any_of(slang.begin(), slang.end(),
                                         [new_word](string s){return s == new_word;});
                    //if not, add it to the list
                    if (!hasWord)
                        slang.push_back(new_word);
                }
            }
            //check for duplicates between the 3 lists and delete if found
            //if in slang, remove from other lists
            for (string word : slang) {
                // remove from casual
                for (auto it = casual.begin(); it != casual.end(); ++it) {
                    if (*it == word)
                        it = casual.erase(it);
                }

                // remove from formal
                for (auto it = formal.begin(); it != formal.end(); ++it) {
                    if (*it == word)
                        it = formal.erase(it);
                }
            }
        }
    }

    //print corpus at the end of simulation
    cout << "After 25 generations: " << endl << endl << endl;
    print_corpus(corpus);
}

//define fuctions
//description: new_slang() returns a substring of the passed string to simulate
// the creation of a new slang word
//arguments: a string (word from the casual or formal list)
//returns: a substring of the passed string (slang for a given word)
string new_slang(string word) {
    //if the passed word is 3 or less letters long
    //reduplicate word
    if (word.length() <= 3)
        return word + word;
    //otherwise just remove the last letter
    else 
    return word.substr(0, word.length() - 1);
}

//description: print_corpus() prints the contents of corpus to the console
//arguments: a map structure (corpus) and a string array (formality)
//returns: void
void print_corpus(map<string, array<list<string>, ARR_SIZE>> corpus) {
    //create formality array to help with output
    array<string, 3> formality = {"Formal", "Casual", "Slang"};
    for (auto c : corpus) {
        cout << "Linguistic Concept: " << c.first << "\n";
        for (int i = 0; i < c.second.size(); ++i) {
            cout << "\t" << formality[i] << ": ";
            auto current = c.second[i];
            for (auto it = current.begin(); it != current.end(); ++it) {
                cout << (*it);
                if (next(it) != current.end()) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}