#include<hmansfml.h>

/* Input: file_name
 * Output: Vector<string> of words from a file
 * Function: Load words from a file into a vector<string>
 */
void setWordList(const std::vector<std::string>& newWordList) 
{
    wordList = newWordList;
}

/* Input: file_name
 * Output: Vector<string> of words from a file
 * Function: Load words from a file into a vector<string>
 */
std::string getRandomWordTest() 
{
    if (wordList.empty()) {
        throw std::runtime_error("Wordlist is empty!");
    }
    srand(static_cast<unsigned>(time(0)));
    return wordList[rand() % wordList.size()];
}

/* Input: file_name
 * Output: Vector<string> of words from a file
 * Function: Load words from a file into a vector<string>
 */
std::string getDisplayWord(const std::string& word, 
                           const std::set<char>& guessedLetters) 
{
    std::string display;
    cout <<"Debug: Actual Word :"<< word  <<endl;
    for (char c : word) {
        if (guessedLetters.count(tolower(c))) {
            display += tolower(c);
        } else if(guessedLetters.count(toupper(c))){
            display += toupper(c);
        }else if(c ==' '){
            display += " ";
        }else{
            display += "_";
        }
        display += " ";
    }
    cout << "Debug: Display String" <<display<<endl;
    return display;
}

/* Input: file_name
 * Output: Vector<string> of words from a file
 * Function: Load words from a file into a vector<string>
 */
vector<string> wordsFromFile(const string& file_name) 
{    
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
        cout << "Obtained File:" <<file_name<<endl;
    } else {
        cout << "Error opening file!" << endl;
    }

    return words_arr;
}

/* Input: Vector<string> of words 
 * Output: string
 * Function: get a random word
 */
string getRandomWord(vector<string>& wordsArr) 
{
    int temp_index = rand() % wordsArr.size();
    string actWord = wordsArr[temp_index];
    return actWord;
}

/* Input: sf::RenderWindow& window, int wrongGuesses
 * Output: void
 * Function: Process each character and create hangman if guess is incorrect
 */

void drawHangman(sf::RenderWindow& window, int wrongGuesses) 
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    // Draw the gallows (always visible)
    // Base
    line.setSize(sf::Vector2f(200, 15));
    line.setPosition(100, 500);
    window.draw(line);

    // Vertical Pole
    line.setSize(sf::Vector2f(15, 300));
    line.setPosition(175, 200);
    window.draw(line);

    // Top Bar
    line.setSize(sf::Vector2f(100, 15));
    line.setPosition(175, 200);
    window.draw(line);

    // Rope
    line.setFillColor(sf::Color::Red);
    line.setSize(sf::Vector2f(10, 60));
    line.setPosition(265, 200);
    window.draw(line);

    line.setFillColor(sf::Color::Blue);

    // Draw hangman parts based on wrong guesses
    if (wrongGuesses >= 1) {
        // Head
        sf::CircleShape head(30);
        head.setFillColor(sf::Color::Transparent);
        head.setOutlineColor(sf::Color::Blue);
        head.setOutlineThickness(5);
        head.setPosition(240, 260);
        window.draw(head);
    }
    if (wrongGuesses >= 2) {
        // Body
        line.setSize(sf::Vector2f(10, 100));
        line.setPosition(265, 320);
        window.draw(line);
    }
    if (wrongGuesses >= 3) {
        // Left Arm
        line.setSize(sf::Vector2f(70, 10));
        line.setPosition(275, 330);
        line.setRotation(135);
        window.draw(line);
        line.setRotation(0); // Reset rotation
    }
    if (wrongGuesses >= 4) {
        // Right Arm
        line.setSize(sf::Vector2f(70, 10));
        line.setPosition(275, 325);
        line.setRotation(45);
        window.draw(line);
        line.setRotation(0); // Reset rotation
    }
    if (wrongGuesses >= 5) {
    
        // Left Leg
        line.setSize(sf::Vector2f(70, 10));
        line.setPosition(275, 420);
        line.setRotation(135);
        window.draw(line);
        line.setRotation(0); // Reset rotation
    }
    if (wrongGuesses >= 6) {
        // Right Leg   
        line.setSize(sf::Vector2f(70, 10));
        line.setPosition(275, 415);
        line.setRotation(45);
        window.draw(line);
        line.setRotation(0); // Reset rotation
    }
}

int setupGameBackground(sf::VideoMode& desktop,sf::RenderWindow& window,  
                        sf::Texture &texture, sf::Sprite& sprite)
{   
    if (!texture.loadFromFile(BACKGROUND)) { 
        std::cerr << "Error: Could not load jpg image!" << std::endl;
        return 0;
    } 

    sprite.setTexture(texture);

    // Scale the background to fit the window
    sf::Vector2u textureSize = texture.getSize();
    sf::Vector2u windowSize = window.getSize();

    // Calculate the scaling factors
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    sprite.setScale(scaleX, scaleY);
    return 1;
}

void setupText(sf::Font& font,sf::Text& wordDisplay, 
               sf::Text& messageDisplay, 
               sf::Text& wrongLettersDisplay)
{
   
    wordDisplay.setFont(font);
    wordDisplay.setCharacterSize(40);
    wordDisplay.setFillColor(sf::Color::Black);
    wordDisplay.setPosition(400, 50);

    messageDisplay.setFont(font);
    messageDisplay.setCharacterSize(35);
    messageDisplay.setFillColor(sf::Color::Green);
    messageDisplay.setPosition(400, 500);
    
    wrongLettersDisplay.setFont(font);
    wrongLettersDisplay.setCharacterSize(35);
    wrongLettersDisplay.setFillColor(sf::Color::Red);
    wrongLettersDisplay.setPosition(400, 400);
}

/* Input: file_name
 * Output: Vector<string> of words from a file
 * Function: Load words from a file into a vector<string>
 */
void initialize(void) 
{
    char action;
    srand(static_cast<unsigned>(time(0)));  // Seed for randomization
    vector<string> words_file;
    wordList = wordsFromFile(FILENAME);
    secretWord = getRandomWord(wordList);
    modSecretWord = secretWord;
    currentWord = string(secretWord.length(), '_');
    int idx = 0;
    while(idx < modSecretWord.length()){
    if(modSecretWord[idx] == ' '){
        modSecretWord.erase(idx,1);
        idx -=2;
        }
        idx++;
    }       
    cout << "Secret Word :"<< secretWord<<" Modified Word:" <<modSecretWord<<endl;
}

/* Input: void
 * Output: integer
 * Function: main function of the file
 */
int main() 
{
    // Fonts and Display Messages
    sf::Font font;
    sf::Text wordDisplay, messageDisplay, wrongLettersDisplay;
    string testExec;
    
    // Load a texture from a JPG file
    sf::Texture texture;

    // Create a sprite for the background
    sf::Sprite sprite;

    // Set up SFML window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, GAMETITLE);
    window.setFramerateLimit(FRAMERATELIMIT);

    // Find out the desktop resolution
    std::cout << "Desktop Resolution: " << desktop.width << "x" << desktop.height << endl;

    if(!setupGameBackground(desktop,window,texture,sprite)){
        std::cout << "Error in Setting up Game Window"<<endl;
        return 0;
    }

    if (!font.loadFromFile(FONTNAME)) { // Replace with a valid font file path
        std::cerr << "Error loading font! "+ FONTNAME << endl;
        return 0;
    }
    setupText(font,wordDisplay, messageDisplay, wrongLettersDisplay);
    initialize();
    // Main Event look
    try {
      
        set<char> guessedLetters;
        set<char> wrongLetters;
        int maxWrongGuesses = 6;
        int wrongGuesses = 0;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Clear the window
                window.clear(sf::Color::White); // Set background color
                // Draw the sprite
                window.draw(sprite);
                // Display the contents of the window
                window.display();

                // Handle keyboard input
                if (event.type == sf::Event::TextEntered) {
                    char inputChar = static_cast<char>(event.text.unicode);
                    if (isalpha(inputChar)) {
                        // Check guess
                        if (modSecretWord.find(tolower(inputChar)) != string::npos ||
                            modSecretWord.find(toupper(inputChar)) != string::npos) {
                            guessedLetters.insert(inputChar);
                        } else if (!guessedLetters.count(inputChar) && !wrongLetters.count(inputChar)) {
                            wrongLetters.insert(inputChar);
                            wrongGuesses++;
                        }
                    }
                }
            }
        
            // Update word display
            string displayWord = getDisplayWord(secretWord, guessedLetters);
            wordDisplay.setString("Current Guess :"+ displayWord);

            // Update wrong letters display
            string wrongLettersStr;
            for (char c : wrongLetters) 
                wrongLettersStr += c + string(" ");
            wrongLettersDisplay.setString("Guessed Letters: " + wrongLettersStr);

            // Update message
            if (displayWord.find('_') == string::npos) {
                messageDisplay.setString("You Win!");
            } else if (wrongGuesses >= MAXATTEMPTS) {
                messageDisplay.setString("You Lose! Word was: " + secretWord);
            } else {
                messageDisplay.setString("Guesses left: " + to_string(MAXATTEMPTS - wrongGuesses));
            }

            // Render
            window.clear();
            window.draw(sprite);   // Draw the background
            window.draw(wordDisplay);
            window.draw(wrongLettersDisplay);
            window.draw(messageDisplay);
            drawHangman(window, wrongGuesses); // Draw the hangman figure
            window.display();

            // End game on win/loss
            if (wrongGuesses >= maxWrongGuesses || displayWord.find('_') == std::string::npos) {
                sf::sleep(sf::seconds(5));
                window.close();
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
