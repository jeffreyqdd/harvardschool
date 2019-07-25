/*
Jeffrey Qian
Compiled using Microsoft Visual Studio Code
programs: hangman2.cpp, dynamic.h, and dynamic.cpp
*/


#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "dynamic.h"
using namespace std;

#define TOTAL_WORDS 9467
#define TOTAL_GUESS 6

//int size = *(&arr + 1) - arr;
//pointers to start loc of string array
struct GameRound{
    string answer = "", current = "";
    char *wrongP, *correctP;
    int wrongWordGuess = 0;
};

//function prototypes
char *append_char(char a[], char s);
char *init_char();
int get_char_length(char c[]);

//returns a fully constructed GameRound
GameRound initialize()
{
    //init
    ifstream fin("filtered.txt");    
    GameRound g;
    
    //seed
    srand(time(0));
    int randNum = rand() % TOTAL_WORDS + 1;

    //get specified word
    string word;
    for(int i = 0; i < randNum; i++)
        getline(fin, word);

    //construct gameround struct
    g.answer = word;
    for(int i = 0; i < g.answer.length(); i++)
        g.current = g.current + "_";
    g.wrongP = init_char();
    g.correctP = init_char();
    
    fin.close();
    return g; 
}

//we shouldn't change gamne in this function
//displays how many chances you have left. 
void display_wrong(const GameRound &game)
{
    // -1 bc we init with '-'
    int totalWrong = get_char_length(game.wrongP) - 1 + game.wrongWordGuess;

    string incorrectDisplay = "[ ";

    for(int i = 0; i < totalWrong && i < TOTAL_GUESS; i++)
        incorrectDisplay = incorrectDisplay + "x" + " ";
    
    for(int i = totalWrong; i < TOTAL_GUESS; i++)
        incorrectDisplay = incorrectDisplay + "-" + " ";

    incorrectDisplay = incorrectDisplay + "]";

    cout << endl << incorrectDisplay << endl;
}

//we shouldn't change game here either
//displays wrongly guess letters given GameRound struct
void display_guesses(const GameRound &game)
{
    cout << "Incorrect Letters";

    int length = get_char_length(game.wrongP);

    char *pc; pc = game.wrongP;
    for(int i = 0; i < length; i++)
    {
        cout <<  *pc++ << " ";
    }

    cout << endl;
}

void update_game(GameRound &game, string s)
{
    //check iof the letter has been guessed before
    if(s.length() == 1)
    {
        for(char *c1 = game.wrongP; *c1; c1++)
        {
            if(*c1 == s[0])
            {
                cout << "You've guessed this before...can't you see?\n";
                return;
            }
        }
        for(char *c2 = game.correctP; *c2; c2++)
        {
            if(*c2 == s[0])
            {
                cout << "You've guessed this before...can't you see?\n";
                return;
            }
        }
    }
    
    bool flag = false;
    char temporary;
    if(s.length() == 1)
    {
        //if it is a letter guess
        //if correct, replaces the dashes with all occurences of the letter
        //iterate through each letter of answer using pointer and if it matches the
        //guess replace the corresponding char in current with the guess.

        temporary = s[0];
        for(int i = 0; i < game.answer.length(); i++)
        {
            if(s[0] == game.answer[i])
            {
                //add correct guess
                game.current[i] = s[0];
                flag = true;
                game.correctP = append_char(game.correctP, temporary);
            }
        }
        //add wrong letter
        if(!flag)
        {
            game.wrongP = append_char(game.wrongP, temporary);
        }

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
        //count wrong word
        if(!flag) game.wrongWordGuess++;
    }
    return;

}
//main code and logic
//call by reference to reduce mem size
void play(GameRound &game)
{
    string guess;

    while(true)
    {
        //update graphics
        for(auto c : game.current)
            cout << c << " ";
        cout << endl;
        display_wrong(game);
        display_guesses(game);

        //guess either a letter or a word
        cout << endl << "Make a guess: ";
        getline(cin, guess);

        //process the guess
        update_game(game, guess);

        //end game if a: correct or b : no more guess
        if(game.answer == game.current)
        {
            cout << endl << "You got the correct answer. Nice Job!\n";

            break;
        }

        //can't forget the minus one
        if(get_char_length(game.wrongP) + game.wrongWordGuess - 1 >= TOTAL_GUESS)
        {
            display_wrong(game);
            cout << endl << "Whoops, looks like you ran out of chances. The correct word was: "
                 << game.answer << endl << endl;
            break;
        }

        //aesthetics
        for(int i = 0; i < 5; i++) cout << endl;
    }
}

int main(void)
{
    //swear free word list from github
    //https://github.com/first20hours/google-10000-english.git

    //filtered using filter.cpp (not part of main program so I'm free to use vector<T>)

    cout << "---------- Welcome to Hangman -----------" << endl;

    GameRound g = initialize();

        
    play(g);

    //deallocate
    //c++ deallocates but the os doesn't change the value
    //so somehow I am still able to access
    //the values after the mem has been deallocated.

    delete[] g.correctP;
    delete[] g.wrongP;

    //reset pointers.
    g.correctP = 0;
    g.wrongP = 0;
 
    cout << "Thanks for playing. Exiting..." << endl;
    
    return 0;
}

