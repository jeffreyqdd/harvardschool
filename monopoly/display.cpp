#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;


namespace Display
{
    int millisecond = 1300; //delay after cout

    void delay(int n)
    {
        this_thread::sleep_for(chrono::milliseconds(n));
    }
    void display_player(string playerName, int balance)
    {
        cout << "\n\n----------" << playerName << ": $" << balance << "----------\n\n" << endl << endl;
        delay(millisecond);
    }

    void display_event(string s)
    {
        cout << s << endl;
        delay(millisecond);
    }

    void display_tile(string pName, int pPosition, string cName, string cDescription)
    {
        //switch from 0 to 1 based indexing
        cout << pName << " has made it to tile " << pPosition + 1 << ":\n\n" 
            << cName << endl
            << ((cDescription == "~") ? "": (cDescription + "\n"))
            << endl;
        delay(millisecond);
    }

    void display_text(string fileName) 
    {
        try
        {
            ifstream fin(fileName);

            if(!fin.is_open())
                throw  "Error: file does not exist";

            while(!fin.eof())
            {
                string line; getline(fin, line);
                cout << line << endl;
            }
        }
        catch(const char* c)
        {
            cout << c << endl;
        }
        
    }
}
