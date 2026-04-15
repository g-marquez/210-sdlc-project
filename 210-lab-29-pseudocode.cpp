//*****************************************************************************
// COMSC-210 | Lab 29 | Gabriel Marquez
// Description: this file outlines the major steps and blocks of code necessary
// for the language evolution simulation SDLC project.
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
int GENERATIONS = 25;

//declare function prototype(s) for different language changes
string new_slang(string);

//define main function
int main() {
    //srand for random chances later on in simulation
    srand(time(0));

    //initialize map to store language concepts
    map<string, array<list<string>, 3>> corpus;

    //read data from file and populate map
    //if file does not open
        //print an error and exit
    //else read data into map
        //for each line, extract concept and word data
        //insert word into appropriate formality list in the array
    //close file
    //manually populating for the purposes of this mockup
    list<string> formal = {"greetings", "salutations"};
    list<string> casual = {"hi", "hello"};
    list<string> slang = {"heyyo", "wassup"};
    array<list<string>, 3> words = {formal, casual, slang};
    corpus.insert(make_pair("Greeting", words));

    //print corpus before simulation
    for (auto c : corpus) {
        cout << "Linguistic Concept: " << 
    }
    
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
}

//define fuctions
//description: new_slang() returns a substring of the passed string to simulate
// the creation of a new slang word
//arguments: a string (word from the casual or formal list)
//returns: a substring of the passed string (slang for a given word)
string new_slang(string word) {
    return word.substr(0, word.length() -1);
}