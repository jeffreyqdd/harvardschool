#include <iostream>
using namespace std;

enum Inventory {hammer, squirt_gun, bird_seed, key};
string strInventory[4] = {"hammer", "squirt gun", "bird seed", "key"};


int main()
{
    int myStuff[4] = {1,2,3,4};

    for(Inventory i = hammer; i < key; i = static_cast<Inventory>(i + 1))
    {
        cout << "You have: " << myStuff[i] << " " << strInventory[i] << endl; 
    }
    
}