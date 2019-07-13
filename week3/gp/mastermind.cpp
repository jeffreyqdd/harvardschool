#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <set>
using namespace std;

#define MAX_COLORS 6


//globals
struct Game{
    string answer[4] = {};
    int totalGuess = 0;
};

vector<string> commands = {"-instructions",
                     "-play 0",
                     "-play 1",
                     "-reload",
                     "-quit"};

string colors[] = {"blue", "red", "purple", "orange", "brown", "green"};

//cout .txt file given file name
void read_file(string fileName)
{
    ifstream fin(fileName);

    cout << endl;
    while(!fin.eof())
    {
        string s; getline(fin,s);
        cout << s << endl;    
    }

    fin.close();
}
//various game generations aka unique colors or not.
//false == unique generation
void generate_game(Game &g, bool repeat)
{
    srand(time(0));


    //set keeps track of generated colors.
    set<string> seen;
    int generated = 0;

    while(generated < 4)
    {
        string s = colors[rand()%MAX_COLORS];


        //only if unique
        if(!repeat)
        {
            //if does exists, continue, and try again
            if(seen.find(s) != seen.end())
                continue;

            //if color doesn't exist, insert and exit.
            seen.insert(s);
        }

        //successfully decided color
        g.answer[generated] = s;
        generated ++;
    }

    //for(auto o : g.answer){cout << o << " "; }cout  << endl;
}

//checks validity of guess: four elements with correct spelling
bool is_valid_guess(vector<string> v)
{
    if(v.size() != 4) return false;

    for(auto o : v)
    {
        bool flag = true;
        for(int i = 0; i < MAX_COLORS; i++)
        {
            if(o == colors[i]) flag = false  ; 
        }
        if(flag) return false;
    }
    return true;
}
//since string.substr() does not fit this situation, I have to write my own
string cut(int a, int b, string s)
{
    string output = "";

    for(int i = a; i < b; i++)
        output += s[i];

    return output;
}

//turns string into 4 items in vector
vector<string> unpack(string s)
{
    //string should be 3 words and three spaces;
    vector<string> unpacked;

    int i, start, stop;
    for(i = 0, start = 0, stop = 0; i < s.length(); i++)
    {
        if(s[i] == ' ')
        {
            stop = i;
            unpacked.push_back(cut(start,stop,s));
            start = i + 1;
        }
    }
    //last color left
    unpacked.push_back(cut(start,s.length(),s));

    /*for(auto o : unpacked)
    {
        cout << '('<< o << ')' << " ";
    }
    cout << endl;*/

    return unpacked;
}
//main logic section of the code
void play(Game &currentRound)
{
    //simple flow chart: guess, update data, update grapics

    while(currentRound.totalGuess < 7)
    {
        //1. make a guess
        cout << "Enter a guess (color1 [space] color2 [space] color3 [space] color4):\n";

        //upack
        string s; getline(cin, s);
        vector<string> usrGuess = unpack(s);

        //check if guess is valid
        if(!is_valid_guess(usrGuess))
        {
            cout << "You did not write the correct colors/format\n";
            continue;
        }

        //2. update data
        currentRound.totalGuess++;

        int black = 0, white = 0;

        //treat as non-distinct. Will encompass distinct case
        //count how many of each color appears
        
        /*
            Works flawlessly for uniques

            Thought process for non -distinct

            say we input r r r r and the answer was r g r g

            we count 2 total g and 2 total r colors in the answer
            
            this way we don't overcount the number of r's

            we process black pegs first so
            black = 2
            white = 0

            input r r g g, answer g g r b

            we count 2 g, 1 r, and 1 b

            we first process blacks
            black = 0

            then we process whites
            r = 1 valid space, g = 2 valid space

            black = 0
            white = 3
        */
        int colorCnt[] = {0,0,0,0,0,0};
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < MAX_COLORS; j++)
            {
                if(currentRound.answer[i] == colors[j]) colorCnt[j] += 1;
            }
        }

        //check black peg
        for(int i = 0; i < 4; i++)
        {

            if(usrGuess[i] == currentRound.answer[i])
            {
                //update color count
                for(int k = 0; k < MAX_COLORS; k++)
                {
                    if(usrGuess[i] == colors[k])
                    {
                            colorCnt[k]--;
                            black++;
                            break;
                    }
                }
            }
        }

        //check white peg
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                //skip same slots
                if(i == j) continue;
                if(usrGuess[i] == currentRound.answer[j])
                {
                    //update color count
                    for(int k = 0; k < MAX_COLORS; k++)
                    {
                        if(( usrGuess[i] == colors[k]) && (colorCnt[k] > 0))
                        {
                            colorCnt[k]--;
                            white++;
                            break;
                        }
                    }
                }
            }
        }

        //cout << black << " : " << white << endl;


        //3. update graphics
        cout << endl << endl << endl;
        cout << '[';
        for(int i = 0; i < 4; i++)
        {
            cout << usrGuess[i];
            if(i < 3) cout << ',';
        }
        cout << ']' << endl;
        cout << "..\n..\n..\n" << "Black: " << black << endl
             << "White: " << white << endl;
        cout << endl << endl << endl;
        //check win
        if(black == 4)
        {
            cout << "That was the correct guess!!\n...returning to main menu...\n\n\n";
            return;
        }
    }
    //lose
    cout << "Sorry, your 7 guesses were used up. \nThe correct answer was: ";
    for(auto o : currentRound.answer){cout << o << " "; }cout  << endl;

}

int main()
{
    //start
    read_file("intro.txt");


    //usr inputs
    while(true)
    {   
        cout << "Enter command: ";
        string reply; getline(cin, reply);

        bool flag = true;
        int i;

        for(i = 0; i < commands.size(); i++)
        {
            //cout << reply << " : " << commands[i] << endl; 
            if(reply == commands[i])
            {
                flag = false;
                break;
            }
        }

        cout << endl;
        if(flag)
        {
            cout << "Invalid command\n";
            continue;
        }
        
        Game currentRound;

        if(i == 0)
        {
            read_file("instructions.txt");
            continue;
        }
        else if(i == 1)
        {
            generate_game(currentRound, false);
        }
        else if(i == 2)
        {
            generate_game(currentRound, true);
        }
        else if(i == 3)
        {
            read_file("intro.txt");
            continue;
        }
        else if(i == 4) break;

        play(currentRound);
    }

    cout << "Thank you for playing!\nclosing game....\n";


    return 0;
}