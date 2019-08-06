#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
using namespace std;

#include "main.h"

void test_money_class()
{
    
    Money bob; //default constructor
    Money joe(2,39); //separate constructor
    Money phil(10.10); //combined constructor


    Money billy = phil;

    billy.overflow();
    billy.show_money();
    
    int dollars, cents;
    cout << "How many dollars do you wish to deposit? "; cin >> dollars;
    cout << "How many cents do you wish to deposit? "; cin >> cents;
    
    billy.increase_money(dollars, cents);
    billy.overflow();
    billy.show_money();

    cout << "How many dollars do you wish to withdraw? "; cin >> dollars;
    cout << "How many cents do you wish to withdraw? "; cin >> cents;

    billy.decrease_money(dollars, cents);

    
    cout << "Adding:\n";
    billy.overflow();
    billy.show_money();
    joe.show_money();

    billy += joe;

    cout << "result: ";
    billy.overflow();
    billy.show_money();

    double d;
    cout << "How much money do you wish to add (double format)? "; cin >> d;
    billy += d;
    
    billy.overflow();
    cout << billy << endl;


    cout << "How much money do you wish to start with (dollars [space] cents): "; cin >> bob;
    bob.overflow();
    cout << bob << endl;

    cout << (bob > joe) << endl;
    cout << (bob < joe) << endl;
    cout << (bob == joe) << endl;
    cout << (bob != joe) << endl;
}

void display_safe_array(SafeArray &arr1)
{
    vector<int> v;
    arr1.copyTo(v);
    for(auto o : v)
        cout << o << " ";
    cout << endl;
}
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


int main()
{
    test_money_class();
    test_safe_array();


    //while(true)test_safe_array(); //test for memory leak.


}

//overflow
void Money::overflow()
{
    if(m_cents >= 0)
    {
        m_dollars += m_cents / 100;
        m_cents = m_cents % 100;
    }
    else
    {
        m_dollars -= (-m_cents) / 100;;
        m_cents = m_cents % 100;
    }
}

//display money
void Money::show_money() const
{

    double combined = static_cast<double>(m_dollars) + m_cents * 0.01;

    printf("Your balance is: $%.2f\n", combined);
}

//increase and decrease balance with parameters dollars and cents
void Money::increase_money(int dollars, int cents)
{
    m_dollars += dollars;
    m_cents += cents;
}
void Money::decrease_money(int dollars, int cents)
{
    m_dollars -= dollars;
    m_cents -= cents;
}

//set functions using integers and double
void Money::set_money(int dollars, int cents)
{
    m_dollars += dollars;
    m_cents += cents;
}
void Money::set_money(double d)
{
    int dollars = d;
    int cents = ((d - dollars) * 100.0) + 0.1; // don't know why. It's always #.9999999999999964
    
    m_dollars = dollars;
    m_cents = cents;
    
}

//default
Money::Money(): m_dollars(0), m_cents(0)
{}

//constructor for individual parameters: dollars, cents
Money::Money(int dollars, int cents): m_dollars(dollars), m_cents(cents)
{}

//constructor for combined dollars and cents
Money::Money(double d)
{
    set_money(d); //no duplicates and deja vu errors.
}

//copy constructor
Money::Money(const Money &m2)
{
    m_dollars = m2.m_dollars;
    m_cents = m2.m_cents;
    printf("Successfully copied money\n");
}

//class destructor
Money::~Money()
{
    printf("Your wallet is now empty\n");
}


void SafeArray::init()
{
    try
    {
        m_startArr = new int[0];
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
}

SafeArray::SafeArray() //default
{
    init();
}

SafeArray::SafeArray(initializer_list<int> l) //initializes using initializer list.
{
    m_startArr = new int[l.size()];
    m_size = l.size();
    copy(l.begin(), l.end(), m_startArr);
}

SafeArray::SafeArray(const SafeArray &obj) //copy
{
    m_startArr = new int[obj.m_size];

    for(int *i = m_startArr,*j = obj.m_startArr, o = 0; o < m_size ; i++, j++, o++)
    {
        *j = *i;
    }

}
void SafeArray::addItems(int howMany, int value) //append
{
    int *newArr; //temporary storage
    newArr = new int[m_size + howMany];

    copy(m_startArr, m_startArr + m_size, newArr);

    for(int i = m_size; i < m_size+howMany; i++) //fill in remaining values
    {
        newArr[i] = value;
    }

    //replace
    m_startArr = nullptr;
    delete[] m_startArr;

    m_startArr = newArr;
    m_size += howMany; //update size

    //clean
    newArr = nullptr;
    delete[] newArr;

}
int SafeArray::at(int index) //get at indexx
{
    try
    {
        if(index > m_size - 1 || index < 0)
            throw out_of_range("Out of range. Returning 0");

        return m_startArr[index];
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
        return 0;
    }
    
}

void SafeArray::put(int index,int data) //replace
{
    try
    {
        if(index > m_size - 1 || index < 0)
            throw out_of_range("Out of range. Aborting put");

        m_startArr[index] = data;    
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
    
}
void SafeArray::put(int index, int* pArr, int howmany) //replace starting at index
{
    try
    {
        for(int i = index; i < index + howmany; i++)
        {
            if(i < 0 || i > m_size) throw out_of_range("Error. Out of range. Aborting put.");

            m_startArr[i] = pArr[i-index];
        }
    }
    catch(const exception& e)
    {
        cout << e.what() << '\n';
    }
}
void SafeArray::copyTo(vector<int>& v) //copy safearray to vector
{
    v.clear();
    for(int i = 0; i < m_size; i++)
        v.push_back(m_startArr[i]);
        
}
int SafeArray::size() //return size
{   
    return m_size;
}
void SafeArray::clear() //deletes everything and resets back to normal.
{
    delete[] m_startArr;

    m_startArr = nullptr;
    m_size = 0;

    init();

}
SafeArray::~SafeArray() //destructor
{
    cout << "deleting SafeArray" <<endl;
    delete[] m_startArr;
}