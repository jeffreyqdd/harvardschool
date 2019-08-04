/*  Some housekeeping. Constants to keep througout the whole program: meanings of symbols and tile type.

    // ! = null, ~ not yet assigned

    Types
    property
    Community_Chest
    Chance
    Jail
    misc
    tax
    railroads

    Classification keywords
    Type:
    Name:
    Description:
    Fee:       
    Owner:
    OwnerCost:
    HouseCost:
    HouseMulti:
    Limit:
    Rate:



Type: Property
Name:
Description:
Owner:
Fee:
OwnerCost:
HouseCost:
HouseMulti:
Limit:
END

*/


//player data

class Player
{
private:
    string m_name;
    int m_balance;
    int m_position;
    int m_type;
public:
    void init(string, int, int, int);

    string get_name() const;
    int get_balance() const;
    int get_position() const;
    int get_type() const;

    void set_balance(int);
    void set_position(int);

    void roll_dice(int&,int&);

};

class Computer: public Player //inheritance 
{
private:
    
public:
    
};

class Tile //individual tile
{
private:
    string m_name;
    string m_description;
    string m_type;
public:

    string get_name() const;
    string get_description() const;
    string get_type() const;

    friend ostream& operator<< (ostream &os, const Tile &obj)
    {
        os << obj.m_name << endl << ((obj.m_description == "~" ? "":obj.m_description)) << endl;

        return os;
    }
    friend class Property;
    friend class Station;
    friend class Tax;
    friend class Misc;
};

class Property: public Tile
{
private:
    string m_owner;
    int m_ownerCost;
    int m_fee;
    int m_houseCost;
    int m_houseMulti;
    int m_limit; 
public:
    void init(string, string, string, string, int, int, int, int, int);
    
    string get_owner() const;
    int get_rent() const;
    
    void set_owner(); //used with buy property
    void set_rent(); //used with buy house
    
    void buy_property();
    void buy_house();
    
};

class Station: public Tile
{
private:
    string m_owner;
    int m_ownerCost;
public:
    void init(string, string, string, string, int);

    string get_owner() const;
    void buy_station();
};

class Tax: public Tile
{
private:
    int m_rate;
public:
    void init(string, string, string, int);
    int get_rate() const;
};

class Misc: public Tile
{
private:
    int m_fee;
public: 
    void init(string, string, string, int);
    int get_fee() const;
};



//commands
namespace UserInputs
{
    vector<string> commands = { "-rules",
                                "-play",
                                "-reload",
                                "-quit" };
}

//game data
namespace Game
{
    Tile board[TOTAL_TILES];
    Player person[MAX_PLAYERS];
    string chance[20];
    string community[20];
};

//prototypes
void load_data();
void load_player_data();
void play_game();