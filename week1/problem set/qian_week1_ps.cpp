/*
Assignment: week 1 problem set
File name:  qian_week1_ps.cpp
Name: Jeffrey Qian
Compiler: Microsoft Visual Studio Code
*/


#include <iostream>
#include <climits>
#include <string>
using namespace std;

/*
Problem 1: declare, define, initialize
*/
void initialize_var()
{
    //age of cat
    int catAge = 4;
    
    //gpa of student
    float studentGpa = 3.7;

    //name of football team
    string teamName = "Seattle Seahawks";

    //num of jelly beans in a hot tub
    int numBeans = 10;

    //whether to eat pizza or not
    bool toEatPizza = true;

    //max num of people allowed in a specific night club.
    const int kMaxOccupancy = 150; 

    return;
}

/*
Problem 2: Ask user for name and address
*/
void ask_info()
{
    string firstName, lastName, streetNum, streetName, streetType, city, state, zip;
    
    cout << "What is your first name? \n";
    getline(cin, firstName);

    cout << "What is your last name? \n";
    getline(cin, lastName);

    cout << "What is your street number? \n";
    getline(cin, streetNum);

    cout << "What is your street name? \n";
    getline(cin, streetName);

    cout << "What is your street type? \n";
    getline(cin, streetType);

    cout << "What is the name of your city? \n";
    getline(cin, city);

    cout << "What is the name of your state \n";
    getline(cin, state);

    cout << "What is your zip code? \n";
    getline(cin, zip);
    
    cout << endl;

    cout << firstName << " " << lastName << endl
         << streetNum << " " << streetName << " " << streetType <<endl
         << city << ", " << state << " " << zip << endl;

    cout << endl;

    return;    
}

/* 
Problem 3: order hotdogs
*/


//round to 2 decimal places
double round_num(double n)
{
    /* 
    for example 11.126
    11.12 * 100 = 1112.6
    1112.6 + .5 = 1113.1
    (int) 1113.1 = 1113
    1113/100 = 11.13
    */
    
    double value = (int)(n * 100 + .5);
    return value / 100;
}

//main code for problem 3
void joes_hotdogs()
{
    int numHotdogs, numFries, numDrinks;
    

    //get usr info
    cout << "Hello valued customer. Welcome to Joe's Hotdog" << endl;

    cout << "How many hotdogs would you like to order?: ";
    cin >> numHotdogs;

    cout << "How many fries would you like to order?: ";
    cin >> numFries;

    cout << "How many drinks would you like to order: ";
    cin >> numDrinks;


    //calculate cost
    double subtotal = numHotdogs * 3.50 + numFries * 2.50 + numDrinks * 1.25,
           tax = round_num(subtotal * 0.0625);


    //give receipt
    cout << endl << endl << endl;

    cout << "Joe's Hotdogs" << endl << endl
         << "Your order:" << endl
         << numHotdogs << " Hotdog" << (numHotdogs == 1 ? "" : "s") << endl
         << numFries << " French " << (numFries == 1 ? "Fry" : "Fries") << endl
         << numDrinks << " Soda" <<  (numDrinks == 1 ? "" : "s") << endl;
        
    cout << endl << endl;

    cout << "Subtotal: $" << subtotal << endl
         << "Meals Tax (6.25%): $" << tax << endl
         << "Total Due: $" << subtotal + tax << endl << endl;

    cout << "Thank you for visiting Joe's Hotdog Stand" << endl;

    return;
}
int main()
{
    initialize_var();

    ask_info();

    joes_hotdogs();

    return 0;
}