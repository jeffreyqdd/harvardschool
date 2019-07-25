#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace Graphics{

    void display_txt(string fileName)
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

}