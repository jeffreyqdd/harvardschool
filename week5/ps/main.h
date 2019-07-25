
//class money for problem #1
class Money
{
    public:
        int m_cents = 0;
        int m_dollars = 0;

    //constructor
    Money()
    {
        m_cents = 0;
        m_dollars = 0;
    }

    //copy constructor
    Money(const Money &m2)
    {
        m_cents = m2.m_cents;
        m_dollars = m2.m_dollars;
    }

    void add_money(int dollar, int cent)
    {
        m_dollars += dollar;
        m_cents += cent;

        //overflow
        m_dollars += m_cents / 100;
        m_cents = m_cents % 100;

        cout << "Transaction was successful" << endl;
    }

    void show_money()
    {
        double d = static_cast<double>(m_dollars) + static_cast<double>(m_cents) / (double) 100;
        cout << setprecision(2) << fixed
             << "Your balance is: $" << d << endl;
    }

};


//struct for question 3.2
struct Name
{
    string fName;
    string lName;

    bool operator<(const Name &n) const{
        return fName < n.fName;
    }
};

//class for question 3.3

class Student
{
    public:
        string m_fName;
        string m_lName;
        vector<int> m_grades;
        double m_average;
    
    //initialize the variables;
    void init(string first, string last, const vector<int> &grades)
    {
        m_fName = first;
        m_lName = last;
        m_grades = grades;
    }

    //calculate the double m_average
    void calculate_avg()
    {
        int sum = 0;
        for(auto o : m_grades)
            sum += o;

        m_average = static_cast<double> (sum) / (double) m_grades.size();
    }
};