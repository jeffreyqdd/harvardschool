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
    void display_player_name(string playerName)
    {
        cout << "----------" << playerName << "----------" << endl << endl;
        delay(1000);
    }

    void display_event(string s)
    {
        cout << s << endl;
        delay(1000);
    }
}
