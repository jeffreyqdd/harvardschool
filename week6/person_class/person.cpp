#include <iostream>
using namespace std;

class Person
{
public:
    string m_name;
    int m_id;
    Person();
    Person(string, int);
    void set(string, int);
    void display();
};

Person::Person(): m_name(""), m_id(0)
{}

Person::Person(string s, int n)
{
    set(s, n);
}
void Person::set(string s, int n)
{
    m_name = s;
    m_id = n;
}

void Person::display()
{
    cout << m_name << " " << m_id << endl;
}
int main()
{
    Person *people = new Person[5];

    people[0].set("Sam", 1);
    people[1].set("Bob", 2);
    people[2].set("Joe", 3);
    people[3].set("Phill", 4);
    people[4].set("Hillary", 5);

    for(int i = 0; i < 5; i++)
    {
        people[i].display();
    }
    delete[] people;
}