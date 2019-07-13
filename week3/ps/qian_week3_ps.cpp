#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <string>
#include <locale>
#include <limits>
#include <vector>
#include "joe.h"
using namespace std;

#define LENGTH 256

namespace JoeShop{
    enum Menu {hotdogs, fries, drinks};
    const double stuffPrice[] = {1.00, 2.00, 3.00};
    string stuffName[] = {"hotdogs", "fries", "drinks"};
    const double shopDiscount = 0.1;
    const double mealTax = 0.0625;
};

namespace ProblemTwo{
    char myString[LENGTH] = {};
    char cleanedStr[LENGTH] = {};
}

namespace CardType{
    enum Suit {club, diamond, heart, spade};
    string suitName[] = {"Club", "Diamond", "Heart", "Spade"};
    
    string rank[] = {"Ace","Two","Three",
                       "Four","Five","Six",
                       "Seven","Eight","Nine",
                       "Ten","Jack","Queen",
                       "King"};


    int cardsLeft = 52;
};
void next_problem(int n)
{
    for(int i = 0; i < 2; i++)
        cout << endl;
    cout << "----------" << "Problem: " << n << "----------\n";
}

//problem 1: Joe's hotdogs v3.0
void display_menu()
{
    cout << setprecision(2) << fixed
         << "Welcome to Joe's Hotdog Shop" << endl << endl << "Our Menu:" << endl << endl
         << "Hotdogs: $" << JoeShop::stuffPrice[JoeShop::hotdogs] << " each" << endl
         << "Fries: $" << JoeShop::stuffPrice[JoeShop::fries] << " each" << endl
         << "Drinks: $" << JoeShop::stuffPrice[JoeShop::drinks] << " each" << endl << endl;
}

bool is_mon()
{   
    time_t t= time(0);
    tm *now = localtime(&t);
    return now->tm_mday == 1;
}


void apply_monday(int &numDogs, int &numFries, int &numDrinks)
{
    if(!is_mon()) return;
    cout << "Today is Monday, therefore you get our buy 3 get 1 free special!!!!!!!!" << endl;

    cout << endl << "Today is Monday. Therefore, you get our buy 3 get 1 free special!\n"
         << "You get: \n"
         << numDogs / 4 << ((numDogs / 4) == 1 ? " Hotdog off\n" : " Hotdogs off\n")
         << numFries / 4 << ((numFries / 4) == 1 ? " Fry off\n" : " Fries off\n")
         << numDrinks / 4 << ((numDrinks / 4) == 1 ? " Drink off\n" : " Drinks off\n");

        //update
        numDogs -= numDogs / 4;
        numFries -= numFries / 4;
        numDrinks -= numDrinks / 4;

    

}
double round_num(double d)
{
    return round(d * 100) / 100;
}

void calculate_total(double &subtotal, double &discount, double &tax, const int order[])
{
    subtotal = round_num(order[JoeShop::hotdogs] * JoeShop::stuffPrice[JoeShop::hotdogs]
               + order[JoeShop::fries] * JoeShop::stuffPrice[JoeShop::fries]
               + order[JoeShop::drinks] * JoeShop::stuffPrice[JoeShop::drinks]);

    if(subtotal >= 20)
    {   
        discount = round_num(subtotal * JoeShop::shopDiscount);
        cout << endl << endl << "Congratulations. You've qualified for our discount\n";
    }
    

    tax = round_num((subtotal - discount) * JoeShop::mealTax);
}

void joe_dog_v_3()
{
    display_menu();


    //get order
    int order[3] = {};


    while (true)
    {
        cout << "What would you like to order?\n" 
             << "1 for " << JoeShop::stuffName[JoeShop::hotdogs] << endl
             << "2 for " << JoeShop::stuffName[JoeShop::fries] << endl
             << "3 for " << JoeShop::stuffName[JoeShop::drinks] << endl
             << "4 to exit\n";

            int answer;
            cin >> answer;

            if(answer - 1 == JoeShop::hotdogs)
            {
                cout << "How many hotdogs would you like to buy? ";
                cin >> order[JoeShop::hotdogs];
            }
            else if(answer - 1 == JoeShop::fries)
            {
                cout << "How many fries would you like to buy? ";
                cin >> order[JoeShop::fries];
            }
            else if(answer - 1 == JoeShop::drinks)
            {
                cout << "How many drinks would you like to buy? ";
                cin >> order[JoeShop::drinks];
            }
            else
            {
                cout << "Processing order...\n";
                break;
            }
            
    }

    //exit if nothing has been ordered
    if(!(order[JoeShop::hotdogs] || order[JoeShop::fries] || order[JoeShop::drinks]))
    {
        cout << "You have not ordered anything\n";
        return;
    }

    
    //print order
    cout << "Joe's Hotdogs" << endl << endl
         << "Your order:" << endl
         << order[JoeShop::hotdogs] << " Hotdog" << (order[JoeShop::hotdogs] == 1 ? "" : "s") << endl
         << order[JoeShop::fries] << " French " << (order[JoeShop::fries] == 1 ? "Fry" : "Fries") << endl
         << order[JoeShop::drinks] << " Soda" <<  (order[JoeShop::drinks] == 1 ? "" : "s") << endl;

    apply_monday(order[JoeShop::hotdogs], order[JoeShop::fries], order[JoeShop::drinks]);

    double subtotal = 0.0, discount = 0.0, tax = 0.0;

    calculate_total(subtotal, discount, tax, order); 


    double adjSub = subtotal - discount,
           finalTotal = adjSub + tax;

    cout << setprecision(2) << fixed << endl << "Subtotal: $" << subtotal << endl
         << "Discount if applicable (10%): -$" << discount << endl
         << "Adjusted Subtotal: $" << adjSub << endl
         << "Meals Tax (6.25%): $" << tax << endl
         << "Total Due: $" << finalTotal << endl << endl;
}   

void clean_text(char s[])
{
    
    //smart search O(n) complexity
    //just use ascii values, therefore no need to "clean"
    //the text of special chars
    
    char cleaned[LENGTH] = {};
    locale loc;

    for(int i = 0, j = 0; i < LENGTH; i++)
    { 
        if(tolower(s[i], loc) >= 'a' &&  tolower(s[i], loc) <= 'z') 
        {
            cleaned[j++] = tolower(s[i], loc);
        }
    }

    strcpy(ProblemTwo::cleanedStr, cleaned);   
}

bool is_pallindrome()
{
    int strLength = strlen(ProblemTwo::cleanedStr);

    for(int i = 0, j = strlen(ProblemTwo::cleanedStr)-1; i < strlen(ProblemTwo::cleanedStr); i++, j--)
    {
        if(ProblemTwo::cleanedStr[i] != ProblemTwo::cleanedStr[j])
            return false;
    }
    return true;
}


//Problem2: check for pallindrome.
bool check_pallindrome()
{

    char myString[LENGTH] = {}; cout << "Enter a phrase: ";
    cin.getline(ProblemTwo::myString,LENGTH);

    clean_text(ProblemTwo::myString);

    return is_pallindrome();
}

//problem 3
vector<string> seen_suit;
vector<string> seen_rank;
int deal_a_card(CardType::Suit &cardSuit, string &cardRank)
{
    int i;
    for(i = 0; i < 13; i++)
    {
        if(CardType::rank[i] == cardRank)
            break;
    }
    return min(i,10);
}

void generate_card()
{
    CardType::cardsLeft --;

    while (true)
    {

        //generate

        int rNum = rand();

        int randomSuitNum = rNum % 4;
        int randomRankNum = rNum % 13;

        CardType::Suit suitType;

        //test 0-3, not 1-4, if 4 --> segmentation fault.
        switch(randomSuitNum)
        {
            case 0:
                suitType = CardType::club;
                break;
            case 1:
                suitType = CardType::diamond;
                break;
            case 2:
                suitType = CardType::heart;
                break;
            case 3:
                suitType = CardType::spade;
                break;
        }
        //cout << "enter" << endl;
        string cardSuit = CardType::suitName[suitType];
        string cardRank = CardType::rank[randomRankNum];
        //cout << "exit" << endl;

        //check
        bool flag = false;

        for(int i = 0; i < seen_suit.size(); i++)
        {
            if(seen_suit[i] == cardSuit && seen_rank[i] == cardRank) flag = true; 
        }

        if(flag) continue;

        //update
        seen_suit.push_back(cardSuit);
        seen_rank.push_back(cardRank);

        if(CardType::cardsLeft <= 7)
        {
            //reset
            seen_suit.clear();
            seen_rank.clear();
            CardType::cardsLeft = 52;

            cout << "re-shuffle\n";
        }
        
        
        cout << deal_a_card(suitType, cardRank) << ": "
             << cardSuit << " " << cardRank << " cards left:" << CardType::cardsLeft << endl;

        break;
    
    }

}
int main()
{
    //seed random num gen
    srand(time(0));


    //problem where problem1 leaves something in the input stream
    //(Can't work it out after hours of debugging)
    //so then problem 2 proceeds to treat it as an usr input
    //I believe this might be a newline char but I can't see it.
    
    //joe_dog_v_3();
    //check_pallindrome();

    while(true)
    {
        string answer;
        cout << "deal a card? y/n: ";
        getline(cin, answer);

        if(answer != "y") break;
        
        generate_card();
    }

    
}