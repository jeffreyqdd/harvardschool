#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


namespace Display
{
    int millisecond = 10; //delay after cout

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
        cout << pName << " has made it to tile " << pPosition << ":\n\n"
            << cName << endl
            << ((cDescription == "~") ? "": (cDescription + "\n"))
            << endl;
        delay(millisecond);
    }
}
