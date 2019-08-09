#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;


class Cypher
{
private:
    int m_key;
    char* m_codedString;
public:
    Cypher(); //default
    Cypher(string); //parameterized constructor. Takes file name.
    Cypher(const Cypher& c); // copy constructor
    ~Cypher(); //destructor

    string get_code() const;
    int get_length() const;
};


int main()
{

    while(true)
    {
    Cypher c1;
    Cypher c2("file.txt");
    Cypher c3=c2;
    cout << c3.get_code() << endl;
    }
    return 0;

}

int Cypher::get_length() const
{
    int cnt = 0;
    for(char* pc = m_codedString; *pc; pc++)
        cnt++;
    return cnt;
}

string Cypher::get_code() const
{
    return static_cast<string>(m_codedString);
}

Cypher::Cypher()
{
    m_key = 0;
    m_codedString = nullptr;
}

Cypher::Cypher(string fileName)
{
    ifstream fin(fileName); //open file
    
    string temporary, dummy;

    fin >> m_key;

    getline(fin, dummy); //flush newline
    getline(fin, temporary);

    //dynamically allocate
    m_codedString = new char[temporary.length()];
    strcpy(m_codedString, temporary.c_str()); //cpy
    fin.close();
}
Cypher::Cypher(const Cypher& c)
{
    char *pc; pc = new char[c.get_length()]; //new mem

    strcpy(pc, c.m_codedString);

    m_codedString = pc;
    m_key = c.m_key;
}
Cypher::~Cypher()
{
    //cout << "freeing mem\n";
    //free allocated memory

    delete[] m_codedString;
    m_codedString = nullptr;

}