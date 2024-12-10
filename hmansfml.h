#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;


// Wordlist to be managed externally
vector<string> testWordList = {"sfml", "hangman", "graphics", "window", "keyboard"};

//File Name  to Word Bank
const string FILENAME  = "Secret_Word_Bank.csv";

//Font Name
const string FONTNAME = "/usr/share/fonts/truetype/msttcorefonts/arial.ttf";

//Font Name
const string GAMETITLE = "Play HangMan to Hang a Man";

//Image Name
const string BACKGROUND = "woods.jpg";

//Frame Rate Limit
const int FRAMERATELIMIT = 60;

//Maximum Number of Attempts
const int MAXATTEMPTS = 6;

//Word List
vector<string> wordList;
string secretWord;
string currentWord;
string modSecretWord;

// API to set wordlist
void setWordList(const std::vector<std::string>& newWordList);

// Load a Vector String of Words from File
vector<string> wordsFromFile(const string&);

// Load a Vector String of Words from File
vector<string> wordsFromFile(const string&);

// Initialize the WordList
void initialize(void);

// Set up the Game Foreground
void setupText(sf::Font&, sf::Text&,sf::Text&, 
               sf::Text&);

// Set up the Game Background
int setupGameBackground(sf::VideoMode&,sf::RenderWindow&,  
                        sf::Texture&, sf::Sprite&);