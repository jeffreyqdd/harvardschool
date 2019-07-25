#include <iostream>
#include <string>
using namespace std;

int main()
{
    char text[] = "this is a test";
    
    //only one line of text;
    text = string(text).substr(0,4).c_str();
    
    
    cout << text << endl; // output : "this"
    return 0;
}