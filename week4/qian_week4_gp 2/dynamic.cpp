#include <iostream>
#include <fstream>
using namespace std;

//dynamic memory functions ----------

//inits a char array. Returns pointer to it
//makes it able to deallocate later.
//gets length of a char array
int get_char_length(char c[])
{
    int length = 0;
    for(char *p = c; *p; p++)
        length++;
    return length;
}

char *init_char()
{
    //create a block of memory and return its location
    char *newArray, *startArray;
    newArray = new char[1];
    if(!newArray)
        exit(-1);
    newArray[0] = '-';
    startArray = newArray;
    return startArray;
}

//similar to push_back(), a.push_back(s)
//but returns pointer to new expanded arr
char *append_char(char a[], char s)
{
    //get length of a
    int length = get_char_length(a);
    
    //create an array that is one larger than a;
    char *newArray, *startArray;
    newArray = new char[length + 1];
    if(!newArray)
        exit(-1);
    
    //populate
    for(int i = 0; i < length; i++)
    {
        newArray[i] = a[i];
    }
    newArray[length] = s;

    //return;
    startArray = newArray;


    //free allocated mem
    delete[] a;


    return startArray;
}

