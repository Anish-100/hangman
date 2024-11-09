#include <iostream> 
#include <string> 
#include <vector> 
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#define STB_PERLIN_IMPLEMENTATION

using namespace std; 
//function headers

bool play();
void initialize();
vector<string> words_from_file(const string& file_name);
string get_random_word(vector<string>& words);
bool guessed_letter(char letter);
bool update_current(char letter);
void game_info();
void drawHangman(int attempts_left);
int main();

// Global Variables
string secret_word;
string current_word;
string printed_word;
string secretWordnotMod;
int attempts_left;
vector<char> guessed_letters;
int temp_index =0;
string file_name = "Secret_Word_Bank.csv";

const int MAX_ATTEMPTS = 6;

// Initialize the game by setting up the secret word and other variables
void initialize() {
    srand(time(0));  // Seed for randomization
    vector<string> words_file = words_from_file(file_name);
    secret_word = get_random_word(words_file);
    current_word = string(secret_word.length(), '_');
    for(int i =0; i< printed_word.length();i++)
    {
        if(printed_word[i] == ' ')
             printed_word[i] == ' ';
        else 
        printed_word[i] = '_';
    }

      // Fill with underscores
    attempts_left = MAX_ATTEMPTS;
    play(); 
}
// Play the game until attempts are exhausted or the word is guessed
bool play() {
    cout << "Welcome, Player!" << endl;

    while (attempts_left > 0 && current_word != secret_word) {
        game_info();
        cout << "Please enter a guess: ";
        char guess;
        cin >> guess;
        cout << endl;
        guess = tolower(guess);  // Make guess case-insensitive

        if (guessed_letter(guess)) {
            cout << "Repeated guess, try again." << endl;
            continue;
        }

        bool correct_guess = update_current(guess);

        if (!correct_guess) {
            attempts_left--;
        }
        drawHangman(attempts_left);
    }

    if (current_word == secret_word) {
        cout << "Congrats, you have won!" << endl
          << " The Word was: " << secretWordnotMod;
        return true;
    } else {
        cout << "You have run out of attempts! The word was: " << secretWordnotMod << endl;
        return false;
    }
}

// Function to load words from a file
vector<string> words_from_file(const string& file_name) {
    ifstream file(file_name);
    vector<string> words_arr;
    string word;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            while (getline(ss, word, ',')) {
                if (word !="")
                    words_arr.push_back(word);
            }
        }
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }

    return words_arr;
}

// Select a random word from the word bank
string get_random_word(vector<string>& words_arr) {
    int temp_index = rand() % words_arr.size();
    string ac_word = words_arr[temp_index];
    printed_word = ac_word;
    secretWordnotMod = ac_word;
    int i =0;
    while (i< ac_word.length()){
        if(ac_word[i] == ' ')
        {
            ac_word.erase(i,1);
            i-=2;
             // used as a backend word
        }
        i++;
    }
    return ac_word;
}

// Check if the letter has already been guessed
bool guessed_letter(char letter) {
    return find(guessed_letters.begin(), guessed_letters.end(), letter) != guessed_letters.end();
}

// Update the current word with the guessed letter
bool update_current(char letter) {
    bool correct_guess = false;
    for (int i = 0; i < secret_word.length(); i++)
    {
        if (tolower(secret_word[i]) == letter) 
        {
            current_word[i] = secret_word[i];
            correct_guess = true;
        }

    }
     for (int i = 0; i < printed_word.length(); i++)
     {
        if (tolower(secretWordnotMod[i]) == letter)
        {
            printed_word[i] = letter;
        }
     }
    guessed_letters.push_back(letter);
    return correct_guess;
}

// Display the current state of the game
void game_info() {
    cout << "Your current guess: " << printed_word << endl;
    cout << "Number of attempts left: " << attempts_left << endl;
    cout << "Guessed letters: ";
    for (char letter : guessed_letters) {
        cout << letter << " ";
    }
    cout << endl;
}

// Main function to start the game
int main() {
    initialize();
    return 0;
}

	void drawHangman(int attempts_left) 
    { 
        // ASCII art Modify this function to display the 
        // hangman as you like 
        if (attempts_left == 5) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
        else if (attempts_left == 4) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
        else if (attempts_left == 3) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
        else if (attempts_left == 2) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
        else if (attempts_left == 1) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |    /" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
        else if (attempts_left == 0) { 
            cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |    / \\" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
        } 
    } 