/*
could you comment on my usages on
#inlcude and what are the best practices?
Thanks.
*/

/*
Jeffrey Qian
week 5 problem set: main.cpp
compiled using visual studio code
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "main.h"

/*
solves problem one.
displays original balance, asks for deposit, and displays new balance
*/
void test_money()
{
    Money m;

    int d, c;
    
    m.show_money();

    cout << "How many dollars do you wish to deposit: ";
    cin >> d;
    cout << "How many cents do you wish to deposit: ";
    cin >> c;

    m.add_money(d,c);
    m.show_money();

    //copy money (never do this in real life)

    Money m2 = m;
    cout << "\n\ncopied successfully...\n\n";
    m2.show_money();
}

/*
solves problem two.
takes string, splits it into numbers, and adds it
*/
void add_str()
{
    string numbers = "1 2 3 4 5 6";
    stringstream ss;
    
    ss << numbers;

    int sum = 0;
    for(int i = 0; i < 6; i++)
    {
        int n; ss >> n;
        sum += n;
    }
    
    cout << sum << endl;
}

/*
solves problem 3 part one
reads names and couts num of lines;
*/

void read_file_1()
{
    ifstream fin("names.txt");

    if(!fin.is_open())
    {
        cout << "Error opening file";
        exit(-1);
    }

    string fName, lName;
    int cnt = 0;
    while(!fin.eof())
    {
        fin >> fName >> lName;
        cout << fName << " " << lName << endl;
        cnt++;
    }

    cout << "There were " << cnt << " names.\n";

    fin.close();
}

/*
solves problem 3 part two
*/
//gets num of lines given file name
int num_lines(string fileName)
{
    int i;
    ifstream fin(fileName);

    if(!fin.is_open())
    {
        cout << "Error opening file\n";
        exit(-1);
    }

    for(i = 0; !fin.eof(); i++)
    {
        string dummy; getline(fin,dummy);
    }
    return i;
}

//reads names, sorts them by first name, and writes to new file
void read_file_2()
{
    int len = num_lines("names.txt");
    
    //files
    ifstream fin("names.txt");
    ofstream fout("sorted.txt");

    if(!(fin.is_open() && fout.is_open()))
    {
        cout << "Error opening file";
        exit(-1);
    }

    vector<Name> names(len);

    //we can do this since the vector size has been initialized to exactly the number of lines in the file
    for(auto &o : names)
        fin >> o.fName >> o.lName;
    
    fin.close();

    //sort by first name
    //comp function within struct itself in main.h
    sort(names.begin(), names.end());

    for(auto &o : names)
        fout << o.fName << " " << o.lName << endl;
    
    fout.close();
}


/*
solves problem 3 part three
*/
//sorting function
//sorts classes based off of highest grade average
bool comp(const Student &a, const Student &b)
{
    return a.m_average > b.m_average;
}
//reads names and grades, sorts the students by class averages, and writes to new file
void read_file_3()
{
    int len = num_lines("students.txt");


    //incorporate gracefully crashing
    try
    {

        //dynamically allocate
        Student *startArr;
        startArr = new Student[len];



        //files
        ifstream fin("students.txt");

        //check if open
        if(!fin.is_open())
        {
            cout << "error opening files\n";
            exit(-1);
        }


        for(int i = 0; i < len; i++)
        {
            //read one student at a time
            string entry; getline(fin, entry);

            //store entry
            stringstream ss; ss << entry;

            string fName, lName;
            vector<int> scores;
            
            //read name
            ss >> fName >> lName;

            //read scores
            while(!ss.eof())
            {
                int n; ss >> n;
                scores.push_back(n);
            }

            //init student class
            Student s;
            s.init(fName,lName,scores); 
            s.calculate_avg();

            //store class
            startArr[i] = s;
        }
        //sort class using comp function written above
        sort(startArr, startArr + len, comp);

        //display
        for(int i = 0; i < len; i++)
        {
            cout << i+1 << ". " << startArr[i].m_fName << " " << startArr[i].m_lName <<": " << startArr[i].m_average << endl;
        }

        //deallocate
        delete[] startArr;

        fin.close();

    }
    catch(...)
    {
         cout << "error\n";
         exit(-2);
    }

}

int main()
{
    cout << "---------\n\n\n";
    test_money();

    cout << "---------\n\n\n";
    add_str();

    cout << "---------\n\n\n";
    read_file_1();
    
    cout << "---------\n\n\n";
    read_file_2();

    cout << "---------\n\n\n";
    read_file_3();
    
    return 0;
}