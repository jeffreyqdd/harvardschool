

//player data

// TODO: Add a BotPlayer
class Player
{
protected:
    string m_name;
    int m_balance;
    int m_position;
    
public:
    bool m_isJail = false; //this should be freely accessible

    Player(string, int, int);

    string get_name() const;
    int get_balance() const;
    int get_position() const;
    int get_type() const;

    void set_balance(int);
    void set_position(int);

    void roll_dice(int&,int&);

    void credit(int); //money into;
    void debit(int); //money out of

    //virtual for polymorphism
    virtual string make_property_decision(int cost) //usr input
    {
        string answer; getline(cin, answer);
        return answer;
    }
    virtual int how_many_house(int cost) //TODO: input filter.
    {
        int howMany; cin >> howMany;
        return howMany;
    }

    ~Player()
    {
        cout << "cleaning player\n";
    }

};

class Bot: public Player
{
private:
    int m_botWeight; //for computer use only [50..100] aggressiveness (50 passive, 100, aggressive)

public:
    //constructor
    Bot(string, int, int, int);

    // calculates percentage of cost in relation to balance..buys if under certain threshold (m_botWeight)
    //takes input cost of property and outputs y/n
    string make_property_decision(int cost) 
    {
        if(cost < m_balance)
        {
            double percentage = (double) cost / (double) m_balance * 100.0;
            if(percentage < m_botWeight)
                return "y";
            else
                return "n";
        }
        else
        {
            return "n";
        }
        
    }

    // calculates how many houses to buy
    int how_many_house(int cost)
    {
        return rand()%4 + 1 ; //[1,4]
    }
    
};

class Tile //individual tile, base class
{
protected: //protected for easy access.
    string m_name;
    string m_description;
    string m_type;

public:
    string get_name() const;
    string get_description() const;
    string get_type() const;

    virtual void tick(Player*)
    {
        cout << "you shouldn't be here" << endl;
    }
    virtual string get_owner() //polymorphism with inheritance classes.
    {
        //will be here if no owner
        return "~";
    }
    virtual void set_owner(string) //you shouldn't even be in this virtual function
    {
        cout << "you shouldn't be here" << endl;
    }
    
    friend ostream& operator<< (ostream &os, const Tile &obj) //operator overide for debugging
    {
        os << obj.m_name << endl << ((obj.m_description == "~" ? "":obj.m_description)) << endl;

        return os;
    }

    ~Tile()
    {
        cout << "destroyed\n";
    }

};

class Property: public Tile //inheritance 
{
private:
    string m_owner;
    int m_ownerCost;
    int m_fee;
    int m_houseCost;
    int m_houseMulti;
    int m_limit; 
public:
    string get_owner();
    void set_owner(string);

    Property(string,string, string, string, int, int, int, int, int);
    
    void update_rent(int); //used with buy house, changes rent cost
    void tick(Player*); //case handling
    
};

class Station: public Tile //inheritance 
{
private:
    string m_owner;
    int m_ownerCost;
public:
    string get_owner();
    void set_owner(string);

    Station(string, string, string, string, int);

    void tick(Player*); //case handling.
};

class Tax: public Tile //inheritance  
{
private:
    int m_rate;
public:
    Tax(string, string, string, int);
    void tick(Player*); //cases
};

class Misc: public Tile //inheritance 
{
private:
    int m_fee;
public: 
    Misc(string, string, string, int);
    
    void tick(Player*); //cases
};



//game data
namespace Game
{
    vector<Tile*> board;
    Player* person[MAX_PLAYERS];
};

//prototypes
void load_data();
void load_player_data();
void play_game();
void unload_data();
void file_for_bankruptcy(Player*);