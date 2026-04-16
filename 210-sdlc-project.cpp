//*****************************************************************************
// COMSC-210 | Lab 30 | Gabriel Marquez
// Description: this file shows the development stage for the language
// evolution simulation SDLC project.
//*****************************************************************************

//Include necessary headers for file handling, data structures, etc.
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <fstream>
#include <random>
using namespace std;

//declare global variable
const int GENERATIONS = 25;
const int FORMAL = 0;
const int CASUAL = 1;
const int SLANG  = 2;

//declare function prototype(s) for different language changes
string new_slang(string);
void print_corpus(map<string, array<list<string>, 3>>);

//define main function
int main() {
    //srand for random chances later on in simulation
    srand(time(0));

    //initialize map to store language concepts
    map<string, array<list<string>, 3>> corpus;

    //read data from file and populate map
    ifstream fin ("corpus.txt");
    if (!fin.good()) {
        cout << "ERROR! Please verify file name and directory and restart program.";
    }
    //if file does not open
        //print an error and exit
    //else read data into map
        //for each line, extract concept and word data
        //insert word into appropriate formality list in the array
    //close file
    //manually populating for the purposes of this mockup
    list<string> formal = {"greetings", "salutations", "g'day", "hello"};
    list<string> casual = {"hi", "howdy", "hey", "hiya"};
    list<string> slang = {"heyyo", "wassup", "whatup", "suhdude"};
    array<list<string>, 3> words = {formal, casual, slang};
    corpus.insert(make_pair("Greeting", words));

    //print corpus before simulation
    print_corpus(corpus);
    
    //begin language evolution simulation
    //for 25 time intervals (generations)
        //iterate through each concept in the map
        //for each concept
            //chance for word to move from one list to another
                //slang->casual, casual->formal
            //chance for word to die
                //erase word from list
            //chance for new slang to be created
                //new_slang

    //manually traversing map for "1 generation" for purpose of mockup
    //making chances all 50% for purposes of mockup (will adjust in alpha and beta)
    for (auto &c : corpus) {
        auto &lists = c.second;
        list<string> &formal = lists[FORMAL];
        list<string> &casual = lists[CASUAL];
        list<string> &slang  = lists[SLANG];
        
        //chance for word to move from slang->casual or casual->formal
        int prob1 = rand() % 100 + 1;
        if (prob1 <= 50) {
            if ((rand() % 100) < 50) {
                //slang->casual
                auto it = slang.begin();
                casual.push_back(*it);
                slang.erase(it);
            }
            else {
                //casual->formal
                auto it = casual.begin();
                formal.push_back(*it);
                casual.erase(it);
            }
        }

        //chance for word to die
        int prob2 = rand() % 100 + 1;
        if (prob2 <= 50) {
            //randomly select one of the 3 lists to erase from
            int rand_list = rand() % 3;
            auto it = lists[rand_list].begin();
            lists[rand_list].erase(it);
        }

        //chance for new slang to be created
        int prob3 = rand() % 100 + 1;
        if (prob3 <= 50) {
            //randomly choose the formal or casual index
            int rand_index = rand() % 2;
            auto it = lists[rand_index].begin();
            string new_word = new_slang(*it);
            slang.push_back(new_word);
        }
    }

    //print corpus at the end of simulation
    print_corpus(corpus);
}

//define fuctions
//description: new_slang() returns a substring of the passed string to simulate
// the creation of a new slang word
//arguments: a string (word from the casual or formal list)
//returns: a substring of the passed string (slang for a given word)
string new_slang(string word) {
    return word.substr(0, word.length() -1);
}

//description: print_corpus() prints the contents of corpus to the console
//arguments: a map (corpus) and a string array (formality)
//returns: a substring of the passed string (slang for a given word)
void print_corpus(map<string, array<list<string>, 3>> corpus) {
    //create formality array to help with output
    array<string, 3> formality = {"Formal", "Casual", "Slang"};
    for (auto c : corpus) {
        cout << "Linguistic Concept: " << c.first << "\n";
        for (int i = 0; i < c.second.size(); ++i) {
            cout << formality[i] << ": ";
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
