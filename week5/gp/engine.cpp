
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>
using namespace std;

#include "engine.h"


int You::display(string file)    //display func. Displays scenario and choices, returns max choices
{
    ifstream fin(file);

    string s;

    for(; s != "@" + to_string(m_currentScene); getline(fin, s));   //navigate to scene
    
    //cout scenario
    while(s[0] != '#')
    {
        if(!(s[0] == '@'))
        {
            for(auto character : s)
            {
                cout << character << flush;
                this_thread::sleep_for(chrono::milliseconds(20));       //cool typing animation
            }
            cout << endl << endl;
        }
        getline(fin,s);
    }

    //fill choice array and display choices;
    int cnt;
    for(cnt = 0; !fin.eof() && s[0] != '@'; cnt++)
    {   

        getline(fin,s);

        if(s[0] == '@') continue;
        stringstream sstr(s); sstr << s;
        Action a; sstr >> a.toGo; //read go to #

        while(!sstr.eof())
        {
            string temporary; sstr >> temporary;
            a.description += temporary + " ";
        }

        m_choices[cnt] = a;
        cout << cnt+1 << ". " << m_choices[cnt].description<< endl;
    
    }
    fin.close();
    //overcnt;
    return --cnt;
}

void You::choose(int n)
{
    if(n==0) return;
     
    int choice;

    while(1)
    {
        try
        {
            cin >> choice;
            throw(choice);
        }
        catch(int choice)
        {
           if(choice >= n + 1)
           {
               cout << "Invalid guess, try again\n";
           }
           else
           {
               break;
           }
           
        }
    }
    m_currentScene = m_choices[choice - 1].toGo;
}

bool You::tick(string file)
{
    int n;
    n = display(file);
    choose(n);

    return n;
}
