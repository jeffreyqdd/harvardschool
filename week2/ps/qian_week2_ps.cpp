#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

//quick function to improve the aesthetics of things
void new_problem(string s)
{
    cout << endl << endl << "-------------" << s << "-------------\n";
}


//Problem 1:
void operator_and_if()
{
    int x = 10, y = 10, z; double d = 0.0 ;
    
    //Add one to x using the = and + operators. Display
    x = x + 1;
    cout << "x + 1 equals " << x << endl;

    //Add one to x using the ++ operator. Display
    x++;
    cout << "x++ equals " << x << endl;
    //Add one to x using the += operator. Display
    x += 1;
    cout << "x += 1 equals " << x << endl;

    //Set y to 4 and z to 8. Divide z by y and store the result in x. Display
    y = 4, z = 8;
    x = z/y; 
    cout << "z / y equals " << x << endl;

    //Divide y by z and store the result in d. Display. (The result should be .5)
    //cout << "test: " << y<< " " << z << endl;
    d = static_cast<double>(y) / static_cast<double>(z);
    cout << "y / z equals " << d << endl;

    //If x is greater than 0, add 10 to x. Display x.
    if(x > 0) x += 10;
    cout << "if(x > 0) then add 10 to x -->" << x << endl;

    //If x is greater than 0 and y is less than 10, add 1 to d. Display x, y, d
    if(x > 0 && y < 10) d += 1;
    cout << x << " " << y << " " << d <<endl;
    
    //If x is greater than 0 or y is less than 10, add 1 to d. Display x, y, d 
    if(x > 0 || y < 10) d += 1;
    cout << x << " " << y << " " << d << endl;
}

/*problem 2 with extra credit*/
//round to 2 decimal places
double round_num(double n)
{
    return round(n * 100) / 100;
}

//whether it is monday(t) or not(f)
bool is_mon()
{   
    //time returns a time_t obj
    time_t t= time(0);
    //convert t to tm struct.
    tm *now = localtime(&t);
    //-> access the member of a struct reference by a pointer.
    //cout << "here: "<< now->tm_mday << endl;

    return now->tm_mday == 1;
}

//main code for problem 2
void joes_hotdogs_updated()
{
    //constants. Good practice.
    const double kPriceDogs = 3.50, kPriceFries = 2.50, kPriceSoda = 1.25,
                 kTax = 0.0625, kDiscount = 0.10;

    //variables
    int numHotdogs = 0, numFries = 0, numDrinks = 0;
    double subtotal = 0.0, tax = 0.0, discount = 0.0;

    //get usr info
    cout << "Hello valued customer. Welcome to Joe's Hotdog" << endl;

    cout << "How many hotdogs would you like to order?: ";
    cin >> numHotdogs;

    cout << "How many fries would you like to order?: ";
    cin >> numFries;

    cout << "How many drinks would you like to order: ";
    cin >> numDrinks;

    //exit if nothing has been ordered
    if(!(numHotdogs || numFries || numDrinks))
    {
        cout << "You have not ordered anything\n";
        return;
    }
    
    //if stuff has been orderd
    //give receipt
    cout << "Joe's Hotdogs" << endl << endl
         << "Your order:" << endl
         << numHotdogs << " Hotdog" << (numHotdogs == 1 ? "" : "s") << endl
         << numFries << " French " << (numFries == 1 ? "Fry" : "Fries") << endl
         << numDrinks << " Soda" <<  (numDrinks == 1 ? "" : "s") << endl;

    //apply buy 3 get 1 free
    //divide by 4 and the # free is the result. Ex: 10 hotdogs: 10 / 4 = 2 --> 2 free
    if(is_mon())
    {
        cout << endl << "Today is Monday. Therefore, you get our buy 3 get 1 free special!\n";
        cout << "You get: \n"
         << numHotdogs / 4 << ((numHotdogs / 4) == 1 ? " Hotdog off\n" : " Hotdogs off\n")
         << numFries / 4 << ((numFries / 4) == 1 ? " Fry off\n" : " Fries off\n")
         << numDrinks / 4 << ((numDrinks / 4) == 1 ? " Drink off\n" : " Drinks off\n");

        //update
        numHotdogs -= numHotdogs / 4;
        numFries -= numFries / 4;
        numDrinks -= numDrinks / 4;
    }

        
    //calculate subtotal
    subtotal = numHotdogs * kPriceDogs + numFries * kPriceFries + numDrinks * kPriceSoda;
        

    //if greater than 20$ calculate the discount
    if(subtotal >= 20)
    {   
        discount = round_num(subtotal * kDiscount);

        cout << endl << endl << "Congratulations. You've qualified for our discount\n";
    }
        

    //apply sales tax
    //sub - discount won't lead to any issues since discount, by default is 0
    tax = round_num((subtotal - discount) * kTax);
        
    //give costs
    double adjSub = subtotal - discount,
        finalTotal = adjSub + tax;
    cout << setprecision(2) << fixed << endl << "Subtotal: $" << subtotal << endl
         << "Discount if applicable (10%): -$" << discount << endl
         << "Adjusted Subtotal: $" << adjSub << endl
         << "Meals Tax (6.25%): $" << tax << endl
         << "Total Due: $" << finalTotal << endl << endl;

    cout << "Thank you for visiting Joe's Hotdog Stand" << endl;
    
    
    
    return;
}

/*
Problem 3: Fibonnaci
use for loop to generate
*/

//generates the sequence
void generate(vector<double> &v, int count, int end)
{
    for(; v.size() < end; count++)
        v.push_back(v[count] + v[count-1]);
}
//asks for length
void fibonacci()
{
    int n = 0;
    cout << "How long do you want the fibonnaci sequence to be? (enter a number larger than 2): ";
    cin >> n;

    //double helps a little with overflow
    vector<double> fib_seq(2); fib_seq[0] = 0; fib_seq[1] = 1;

    generate(fib_seq, 1, n);

    //display
    for(auto o : fib_seq)
        cout << setprecision(0) << fixed << o << " ";
    cout << endl;
}

int main()
{
    //cout << is_mon() << endl;
    new_problem("Problem 1");
    operator_and_if();

    
    new_problem("Problem 2");
    joes_hotdogs_updated();

    new_problem("Problem 3");
    fibonacci();


    return 0;
}