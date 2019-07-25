//I have newfound respect for vectors

/*
Assignment: week 4 problem set
File name:  qian_week4_ps.cpp
Name: Jeffrey Qian
Compiler: Microsoft Visual Studio Code
*/


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FIBONNACI_LENGTH 30

namespace Fibonnaci1{
    int fibArr[FIBONNACI_LENGTH] = {0,1};
}

namespace Name{
    struct Person{
        string firstName;
        string lastName;
    };
}

namespace Money{
    struct Balance{
        int dollars;
        int cents;
    };
}

//problem 1, part 1
//generates fib arr of size 30 and displays using pointers
void fib_part_1(int fib[])
{
    int *p1, *p2;
    
    //set pointers to arr and arr + 1
    
    p1 = fib;
    p2 = fib + 1;


    for(int i = 0; i < FIBONNACI_LENGTH; i++)
    {
        int sum = *p1 + *p2;

        p1++;
        p2++;
        
        //p2 is now in the next position (empty since it was intialized to 0),
        //so we can just set that as sum;
        *p2 = sum; 
    }


    //now display using pointers
    int *px; px = fib;

    for(int i = 0; i < FIBONNACI_LENGTH; i++, px++)
    {
        cout << *px << " ";
    }
    cout << endl;
}

//problem 1, part 2
//take length and generates an array of size length and returns
//pointer to the first item of that array.
int* make_fib_series(const int arrLength)
{ 
    int *dynamicArr, *startArr;

    //request space
    dynamicArr = new int[arrLength];

    if(!dynamicArr)
    {
        cout << "mem error\n";
        exit(-1);
    }

    //init
    if(arrLength >= 0)
        dynamicArr[0] = 0;
    if(arrLength >= 1)
        dynamicArr[1] = 1;


    //generate sequence
    for(int i = 2; i < arrLength; i++)
    {
        //current = sum of last 2 items;
        dynamicArr[i] = dynamicArr[i-1] +  dynamicArr[i - 2];
    }

    startArr = dynamicArr;

    return startArr;
}

//problem 3
//Asks first and last name
//returns pointer to struct Person
Name::Person* alloc_name()
{
    string fName, lName; 
    cout << "What is your first name? ";
    getline(cin, fName);

    cout << "What is your last name? ";
    getline(cin, lName);

    Name::Person *memLoc;

    memLoc = new Name::Person;

    if(!memLoc)
    {
        cout << "Mem error\n";
        exit(-1);
    }

    memLoc -> firstName = fName;
    memLoc -> lastName = lName;

    return memLoc;
}

//add d dollars and c cents to balance person
//fix overflow c > 100
void addMoney(Money::Balance &person, const int &d, const int &c)
{
    person.dollars += d;
    person.cents += c;

    //overflow
    //integer division
    if(person.cents >= 100)
    {
        person.cents -= 100;
        person.dollars += 1;

    }
}

//displays the dollars and cents in balance person
void showMoney(const Money::Balance &person)
{
    cout << "You have: $" << person.dollars << "." << person.cents << endl; 
}


//problem 4, get substring from char array c from index a with length b;
//-1, by default is end of char,
char* substring(char c[], int a, int b = -1)
{
    //get length of char arr
    int length = 0;
    for(char *p = c; *p; p++)
        length++;

    //update b
    (a + b > length || b == -1) ? b = length : b = b;
    //create char arr
    char *arr, *ptr;

    arr = new char[b];

    if(!arr)
        exit(-1);

    //init
    for(int i = 0; i < b - a; i++)
        arr[i] = '\0';

    //cpy. i indexes new arr, j indexes orig arr
    for(int i = 0, j = a; j < a + b; j++, i++)
    {
        arr[i] = c[j];
    }
    
    //return pointer to new arr
    return arr;
    
}

int main()
{
   //-----------------------------------------------------------
    cout << endl << endl << "------PROBLEM 1------" << endl << endl;
    fib_part_1(Fibonnaci1::fibArr);

    cout << endl << endl << "------PROBLEM 1.2------" << endl << endl;
    cout << "How many numbers of the fibonnaci do you want?\n";
    int answer; cin >> answer;
    //flush newline char
    string dummy; getline(cin,dummy);
    int *arrPtr, *arrStart;
    arrPtr = make_fib_series(answer);
    arrStart = arrPtr;

    for(int i = 0; i < answer; i++,arrPtr++)
        cout << *arrPtr << " ";
    cout << endl;
    
    //deallocate
    delete[] arrStart;

    //-----------------------------------------------------------
    cout << endl << endl << "------PROBLEM 2------" << endl << endl;
    Name::Person *personPtr;
    personPtr = alloc_name();

    //dereference
    cout << "Hello, " << "your name is: " << personPtr -> firstName << " "
         << personPtr -> lastName << endl; 
    delete personPtr;

    //-----------------------------------------------------------
    cout << endl << endl << "------PROBLEM 3------" << endl << endl;
    //why bob? it's a cool name
    Money::Balance bob = {20, 19};
    addMoney(bob, 3, 75);
    showMoney(bob);
    

    

    //-----------------------------------------------------------
    cout << endl << endl << "------PROBLEM 4------" << endl << endl;
    //char arr with a ptr
    char cStr[] = "Hello There", *cPtr;

    //ptr points to starting loc of substr arr
    cPtr = substring(cStr, 3, 4);

    for(char *p = cPtr; *p; p++)
        cout << *p << endl;

    //deallocate
    delete[] cPtr;

    return 0;
}