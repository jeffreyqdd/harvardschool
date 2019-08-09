#include <iostream>
#include <fstream>
#include <vector>
#include <initializer_list>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include "main.h"


/*
Problem 1: improve safe array function and add class ArrayBoundException for throw and catch.
*/
//accepts a call to reference to SafeArray
//uses the copy function to copy to vector and display it
void display_safe_array(const SafeArray &arr1)
{
    vector<int> v;
    arr1.copyTo(v);
    for(auto o : v)
        cout << o << " ";
    cout << endl;
}

//function to test the safe array class
void test_safe_array()
{
    SafeArray arr1{1,2,3,4,5,6};

    cout << "original arr: "; display_safe_array(arr1);

    cout <<"arr[3]=" <<arr1.at(3) << endl;
    cout <<"arr[6]=" <<arr1.at(6) << endl;

    cout << "appending 5 8's: ";
    arr1.addItems(5,8);
    display_safe_array(arr1);
    

    cout << "arr[3] = -3: "; arr1.put(3,-3);
    display_safe_array(arr1);

    int* pArr; pArr = new int [3];
    for(int i = 0; i < 3; i++) pArr[i] = -10;

    cout << "arr[0] = [-10,10,10]:" ; arr1.put(0, pArr, 3);
    display_safe_array(arr1);

    delete[] pArr;
}

/*
Problem 2: display each word and its frequency

//the more elegant the solution the better.
*/

//accepts char c..checks if it is punctuation
//returns bool
bool ispunc(char c)
{
    int cInt = static_cast<int>(c);

    if(cInt < 65 || (cInt > 90 && cInt < 97) || cInt > 122) //Ascii table values
        return true;

    return false;
}
void to_lower(string& s)
{
    for(auto& c : s)
    {
        if(c >= 'A' && c <= 'Z')
            c += 32;
    }
}

//accepts a call by reference to directly write into lyrics and a string containing the file name
//appends lowercase and punctuation free word to lyrics.
void strip(vector<string> &v, string fileName)
{
    ifstream fin(fileName);

    while(!fin.eof())
    {
        string word; fin >> word;
        
        //remove punctuation and capitalization;
        word.erase(remove_if(word.begin(), word.end(), ispunc), word.end());
        to_lower(word);

        //append
        v.push_back(word);
    }
}


void ampie()
{
    vector<string> lyrics;


    strip(lyrics, "ampie.txt"); //essentially O(n) complexity

    //my decision is to sacrifice memory for performance
    
    
    //map.find(K) has a complexity of O(log n)
    //we are iterating for every word in the lyrics
    //results in O(n log n ) complexity

    map<string, int> cnt;
    for(auto u : lyrics)
    {
        if(cnt.find(u) == cnt.end())
            cnt[u] = 1; //word does not exist yet
        else
            cnt[u] += 1; //word does exist. Add to frequency.
    }

    //copy and sort also involves O(n log n) complexity

    set<Text> sorted;
    for(auto item : cnt)
        sorted.insert({item.first, item.second});

    //cout
    for(auto t : sorted)
        cout << t.word << ": " << t.freq << endl;
}


//
int main()
{
    //test_safe_array();


    //while(true) test_safe_array(); //test for memory leaks.

    ampie();
}