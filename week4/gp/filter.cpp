//one time use only
//this is not part of the project, therefore it is freed from the "no-vector"
//constraint

//I am merely using it to clean the dict.txt file

#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("dict.txt");
    ofstream fout("filtered.txt");

    vector<string> v;

    while(!fin.eof())
    {
        string s; getline(fin,s);

        if(s.length() < 3)
            continue;

        v.push_back(s);
    }

    for(auto word : v)
        fout << word << endl;

    fin.close();
    fout.close();
}