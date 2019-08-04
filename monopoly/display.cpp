#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


namespace Display
{
    void delay(int n)
    {
        this_thread::sleep_for(chrono::milliseconds(n));
    }
    void display_player(string playerName, int balance)
    {
        cout << "----------" << playerName << ": $" << balance << "----------" << endl << endl;
        delay(1000);
    }

    void display_event(string s)
    {
        cout << s << endl;
        delay(1000);
    }

    void display_tile(string pName, int pPosition, string cName, string cDescription)
    {
    cout << pName << " has made it to tile " << pPosition << ":\n\n"
         << cName << endl
         << ((cDescription == "~") ? "": (cDescription + "\n"))
         << endl;

    }
}
