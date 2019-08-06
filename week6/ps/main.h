class Money
{
private:
    int m_dollars;
    int m_cents;
public:
    Money();    //default
    Money(int,int=0); //int init: (dollars, cents)
    Money(double); //double init $dollars.cents
    Money(const Money&); //copy constructor
    
    //prevent any overflow;
    void overflow();

    void set_money(int,int);
    void set_money(double);

    void increase_money(int,int);
    void decrease_money(int,int);

    void show_money() const;

    //operator
    void operator+= (const Money &obj)
    {
        
        this -> m_dollars += obj.m_dollars;
        this -> m_cents += obj.m_cents;

    }

    void operator+= (const double &d)
    {

        int dollars = d;
        int cents = ((d - dollars) * 100.0) + 0.1; // don't know why. It's always #.9999999999999964
    
        this -> m_dollars += dollars;
        this -> m_cents += cents;
    
    }
    
    friend ostream& operator<< (ostream &os, const Money &obj)
    {
        os << "$" << obj.m_dollars<<"."<< obj.m_cents;
        return os;
    }

    friend istream& operator>> (istream &is, Money &obj)
    {
        is >> obj.m_dollars >> obj.m_cents;

        return is;
    }

    bool operator< (const Money &m)
    {
        if(this -> m_dollars == m.m_dollars)
            return this -> m_cents < m.m_cents;
        return this -> m_dollars < m.m_dollars;
    }

    bool operator> (const Money &m)
    {
        if(this -> m_dollars == m.m_dollars)
            return this -> m_cents > m.m_cents;
        return this -> m_dollars > m.m_dollars;
    }

    bool operator== (const Money &m)
    {
        return (this -> m_dollars == m.m_dollars && this -> m_cents == m.m_cents); 
    }

    bool operator!= (const Money &m)
    {
        return !(this -> m_dollars == m.m_dollars && this -> m_cents == m.m_cents); 
    }

    ~Money(); //class destructor
};





class SafeArray
{
private:
    int *m_startArr;
    int m_size;
public:
    SafeArray(); //default
    SafeArray(initializer_list<int>);
    SafeArray(const SafeArray &); //copy

    void init();
    void addItems(int, int=0);
    int at(int);
    void put(int,int);
    void put(int, int*, int);
    void copyTo(vector<int>&);
    int size();
    void clear();

    ~SafeArray();
};

