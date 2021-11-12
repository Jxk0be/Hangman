#include <iostream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

string NewWord(vector <string> &words, unsigned int &size);

int main() {
    /* Variable Declarations */
    vector <string> wordList;
	vector <vector <string> > hangman;
	vector <string> tVec;
    ifstream fin;
	ifstream hin;
    string words;
	string hang;
    string temp;
    unsigned int size = 0;
	unsigned int underScores = 0;
	unsigned int incorrect = 0;
    string letters = "";
    string guesses = "";
    size_t totalGuesses = 0;
    char command;
    srand (time(NULL));

    /* Opens "hang_data.txt", if it can't, we return an error and print to stderr */
    fin.open("data/hang_data.txt");
    if (!(fin.is_open())) {
        cerr << "FOUL: 'hang_data.txt' could not open\n";
        return -1;
    }

	/* Opens "hang_image.txt", if it can't we return an error and print to stderr */
	hin.open("data/hang_image.txt");
	if (!(hin.is_open())) {
		cerr << "FOUL: 'hand_image.txt' could not open\n";
		return -1;
	}

	/* Reading in the images of the hangman for later on, storing them in a vector of vector of strings */
	while (getline(hin, hang)) {
		if (hang == "~") {
			hangman.push_back(tVec);
			tVec.clear();
		}
		else {
			tVec.push_back(hang);
		}
	}

    /* Reads in every word from the "hang_data.txt" file */
    while (getline(fin, words)) {
        wordList.push_back(words);
    }

    /* Beginning Print Title/Info */
    printf("------------------\nLet's play Hangman\n------------------\n");
    printf("1. Enter '!' to quit the game\n\n");
    printf("Let the game begin, guess a letter\n");
	
	/* Grabbing a word randomly from read in words list. Also, storing size of word in underScores variable */
    temp = NewWord(wordList, size);
	underScores = size;
    
    /* Printing the '_' for every character of the word */
    for (unsigned int i = 0; i < size; ++i) {
        letters = letters + '_';
    }
    for (unsigned int i = 0; i < letters.size(); ++i) {
        if (i == (letters.size() -1)) {
            cout << letters[i] << '\n';
        }
        else {
            cout << letters[i] << ' ';
        }
    }

	/* Loop to grab letters or exit command */
    while (cin >> command) {
        command = tolower(command);
        size_t counter = 0;

        /* This section includes '!' to quit, alongside error checks */
        if (command == '!') return 0;
        if (command < 'a' || command > 'z') {
            printf("Invalid guess: try a letter A-Z\n");
            continue;
        }
        for (unsigned int i = 0; i < guesses.size(); ++i) {
            if (command == guesses[i]) {
                printf("Invalid guess: '%c' has already been guessed\n", command);
                goto end;
            }
        }
        
        /* Counts the total number of valid guesses made */
        ++totalGuesses;

        /* Replaces '_' with correctly guesses characters */
        for (unsigned int i = 0; i < size; ++i) {
            if (command == temp[i]) {
                letters[i] = command;
            }
        }

        /* Counts the '_' to determine if the word has been figured out or not, if so, print final information */
        for (unsigned int i = 0; i < size; ++i) {
            if (letters[i] == '_') ++counter;
        }

		/* If the counter is equivalent to the underScores, we know that the given letter wasn't in the word, so increment incorrect */
		if (counter == underScores) {
			++incorrect;
			cout << '\n';

			/* Everytime we have an incorrect letter, we need to print the hangman */
			for (unsigned int i = 0; i < hangman[incorrect - 1].size(); ++i) {
				cout << hangman[incorrect - 1][i] << '\n';
			}
			cout << '\n';

			/* If the # of incorrect letters equals the # of hangman images, the user has lost the game */
			if (incorrect == hangman.size()) {
				printf("Sorry, you lost.\n");
				printf("------------------INFO------------------\n");
				cout << "Word: \"" << temp  << "\"\n";
				printf("----------------------------------------\n");
				return 0;
			}
		}

		/* Updating the count of underScores each iteration of this loop to compare for next iteration */
		underScores = counter;
		
        if (counter == 0) {
            printf("\nCongratulations! You guessed the word.\n");
            printf("\n------------------INFO------------------\n");
            cout << "Word: \"" << letters << "\"\n";
            cout << "Total Guesses: " << totalGuesses << '\n';
            printf("----------------------------------------\n");
            return 0;
        }

        /* Prints the word to guess, updates alongside the user's guesses */
        for (unsigned int i = 0; i < letters.size(); ++i) {
            if (i == (letters.size() -1)) {
                cout << letters[i] << '\n';
            }
            else {
                cout << letters[i] << ' ';
            }
        }

        /* Adds guesses given by user and prints to the screen */
        guesses = guesses + command;
        printf("Guessed: ");
        for (unsigned int i = 0; i < guesses.size(); ++i) {
            if (i == guesses.size() -1) {
                cout << guesses[i] << '\n';
            }
            else {
                cout << guesses[i] << ' ';
            }
        }
		end:;
    }
    
    /* Returning 0 like a good little programmer boy */
    return 0;
}

string NewWord(vector <string> &words, unsigned int &size) {
    string temp;

    /* Saving random word and its size from the vector */
    temp = words[rand() % words.size()];
    size = temp.size();
    
    return temp;
}
