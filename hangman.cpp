/*
	File: hangman.cpp

	A simple command-line hangman game.
	It uses the file wordBank.txt (one word per line) to get the bank of words,
	then it selects a random word from the bank, and the game begins.
*/


# include <algorithm>
# include <cstdlib>
# include <ctime>
# include <fstream>
# include <iostream>
# include <vector>

# define MAXTRIES 6

using namespace std;

// prints all the letters the player has already guessed
void printGuessedLetters(vector<char> guessedLetters){
	cout << "Guessed letters: ";
	for(unsigned i=0;i<guessedLetters.size();i++){
		cout <<"   "<< char(toupper(guessedLetters[i]));
	}

	cout <<endl<<endl;
}

// prints the hidden word with the guessed letters
void printCurrentGuess(vector<bool> currentGuess, string word){
	for(size_t i =0; i< word.size(); i++){
		cout <<"\t";
		if(currentGuess[i] == true){
			cout << char(toupper(word[i]));
		}else{
			cout << "_";
		}
	}
	cout <<endl<<endl;
}

// returns true if the guessed letter is in the hidden word
// in the process, it updates the currentGuess boolean vector and lettersFound, which
// keeps track of the total letters of the word found by the player
bool isGuessCorrect(char c, vector<bool> &currentGuess, string word, int& lettersFound){
	bool bCorrect = false;
	for(size_t i = 0; i<word.size();i++){
		if(toupper(c) == toupper(word[i])){
			bCorrect = true;
			lettersFound++;
			currentGuess[i] = true;
		}
	}

	return bCorrect;
}


int main(){
	bool bGameOver = false;
	string word;
	int wordLen;

	vector<char> guessedLetters;
	vector<char>::iterator itGuessedLeters;
	vector<string> stages = {
	"\n\t +---+\n\t |   |\n\t     |\n\t     |\n\t     |\n\t     |\n\t=========\n",
	"\n\t +---+\n\t |   |\n\t O   |\n\t     |\n\t     |\n\t     |\n\t=========\n",
	"\n\t +---+\n\t |   |\n\t O   |\n\t |   |\n\t     |\n\t     |\n\t=========\n",
	"\n\t +---+\n\t |   |\n\t O   |\n\t/|   |\n\t     |\n\t     |\n\t=========\n", 
	"\n\t +---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t     |\n\t     |\n\t=========\n",
	"\n\t +---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t/    |\n\t     |\n\t=========\n",
	"\n\t +---+\n\t |   |\n\t O   |\n\t/|\\  |\n\t/ \\  |\n\t     |\n\t=========\n"};
	int curStage = 0;
	int lettersFound = 0;

	char input;
	vector<string> listOfWords;
	string w;

	// populating list of words
	fstream f;
	f.open("wordBank.txt", fstream::in);
	while(getline(f, w)){
		listOfWords.push_back(w);
	}
	f.close();

	// choosing a random word from the word bank
	srand((int)time(0));
	word = listOfWords[rand() % listOfWords.size()];
	// remove escape character(?) at the end of word
	word.pop_back();
	wordLen = word.length();
	vector<bool> currentGuess(wordLen, false);

	cout << stages[curStage]<<endl;
	printCurrentGuess(currentGuess, word);

	while(1){
		cout << "Make a guess"<<endl;
		cout <<"> ";
		cin >> input;

		// check if player has already used that same letter
		// if they haven't, we add it to the list of used letters
		itGuessedLeters = find(guessedLetters.begin(), guessedLetters.end(), input);
		if(itGuessedLeters != guessedLetters.end()){
			cout << "You have already made that guess!"<<endl;
			printGuessedLetters(guessedLetters);
			continue;
		}else{
			guessedLetters.push_back(input);
		}

		if(isGuessCorrect(input, currentGuess, word, lettersFound)){
			cout << input <<" is a letter in the word!"<<endl;
		}else{
			cout << "Wrong guess!"<<endl;
			curStage++;
		}

		printGuessedLetters(guessedLetters);
		cout << stages[curStage]<<endl;
		printCurrentGuess(currentGuess, word);

		if(curStage == MAXTRIES){
			bGameOver = true;
			cout << "GAME OVER!\nThe correct answer was "<< word<<endl;

		}
		else if(lettersFound == wordLen){
			bGameOver = true;
			cout << "Congratulations! You won! The word was "<< word << endl;
		}
		
		if(bGameOver){
			cout << "Do you want to play again? (y/n)"<<endl;
			cin >> input;

			if(input == 'y'){
				bGameOver = false;
				curStage = 0;
				lettersFound = 0;
				currentGuess = {};
				guessedLetters = {};

				word = listOfWords[rand() % listOfWords.size()];
				word.pop_back();
				wordLen = word.length();
				for(size_t i = 0; i< wordLen; i++){
					currentGuess.push_back(false);
				}

				cout << stages[curStage]<<endl;
				printCurrentGuess(currentGuess, word);

			}
			else{
				return 0;
			}
		}

	}

	return 0;
}
