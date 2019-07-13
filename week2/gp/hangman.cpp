#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

//head, body, 2 arms, 2 legs
#define TOTAL_GUESS 6

//helps keep all the variables in one place
struct GameRound
{
    string answer = "", current = "";
    vector<string> wrongLetters;
    vector<string> wrongWords;
    vector<string> correctLetters;

};

/* initializes the struct with values*/
//we shouldn't change v in this function
GameRound initialize(const vector<string> &v)
{
    cout << endl << endl << "- - - Game Starting - - -" << endl << endl;
    
    GameRound game;
    
    //generate random word
    srand(static_cast<unsigned int>(time(0)));
    game.answer = v[rand() % v.size()];

    for(int i = 0; i < game.answer.length(); i++)
        game.current = game.current + "_";
    
    //cout << game.answer << endl << game.current << endl;
    
    return game;
}

//function protypes used in play
void display_guesses(const GameRound &game);
void display_wrong(const GameRound &game);
void update_game(string s, GameRound &game);

/*
The heart of this code
*/
void play(GameRound &game)
{
    string guess;
    
    while (true)
    {
        //update graphics
        cout << endl << game.current << endl;
        display_wrong(game);
        display_guesses(game);
        

        //guess: either a letter or a word
        cout << endl << "Make a guess: ";
        getline(cin, guess);

        //process guess
        update_game(guess, game);

        //end the game if the user guess correct
        if(game.answer == game.current)
        {
            cout << endl << "You got the correct answer, "
                 << game.answer <<  ", in: "
                 << game.correctLetters.size() + game.wrongLetters.size() + game.wrongWords.size()
                 << " tries" << endl << endl;

            break;
        }

        //end game if the user runs out of guesses
        if(game.wrongLetters.size() + game.wrongWords.size() == TOTAL_GUESS)
        {
            display_wrong(game);
            cout << endl << "Whoops, looks like you ran out of chances. The correct word was: "
                 << game.answer << endl << endl;

            break;
        }

        //add new lines
        for(int i = 0; i < 5; i++) cout << endl;
    }
}

int main()
{

    //swear free word list from github
    //https://github.com/first20hours/google-10000-english.git
    ifstream fin("dict.txt");

    //read
    vector<string> wordList;
    while(!fin.eof())
    {
        string s; fin >> s;
        if(s.length() >= 5)
            wordList.push_back(s);
    }

    fin.close();

    string again;

    cout << "---------- Welcome to Hangman -----------" << endl;
    while (true)
    {
        GameRound g = initialize(wordList);
        play(g);

        cout << "Would you like to play again? (y/n): ";
        getline(cin,again);
        if(again != "y")
            break;
    }
    
    cout << "Thanks for playing. Exiting..." << endl;

    return 0;
}


//display functions

//we shouldn't change game in this function
void display_wrong(const GameRound &game)
{
    int totalWrong = game.wrongLetters.size() + game.wrongWords.size();
    string incorrectDisplay = "[ ";

    for(int i = 0; i < totalWrong; i++)
        incorrectDisplay = incorrectDisplay + "x" + " ";
    
    for(int i = totalWrong; i < TOTAL_GUESS; i++)
        incorrectDisplay = incorrectDisplay + "-" + " ";

    incorrectDisplay = incorrectDisplay + "]";

    cout << endl << incorrectDisplay << endl;
}

//we shouldn't change game in this function
void display_guesses(const GameRound &game)
{
    string letters = "Incorrect letters: ";
    string phrases = "Incorrect words: ";

    for(auto o : game.wrongLetters)
        letters += o + " ";

    for(auto o : game.wrongWords)
        phrases += o + " ";

    cout << endl << letters << endl << phrases << endl;
}

//takes input string, guess
//also will take a pass by reference GameRound in order to directly modify it
void update_game(string s, GameRound &game)
{
    bool flag = false;
    if(s.length() == 1)
    {
        //if it is a letter guess
        //if correct, replaces the dashes with all occurences of the letter
        for(int i = 0; i < game.answer.length(); i++)
        {
            if(s[0] == game.answer[i])
            {
                //add correct guess
                game.current[i] = s[0];
                flag = true;
                game.correctLetters.push_back(s);
            }
        }
        //add wrong letter
        if(!flag) game.wrongLetters.push_back(s);

    }
    //treat as entire word
    else
    {
        if(s == game.answer)
        {
            //add correct guess
            game.current = s;
            flag = true;
        }
        //add wrong word
        if(!flag) game.wrongWords.push_back(s);
    }
    return;
}
