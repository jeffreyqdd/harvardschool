#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "gamerule.h"
#include "main.h"
#include "display.h"

//UI, loads game, generates data, and calls play game func
int main()
{
    //all main is is UI.
    //Graphics::display_txt("text/intro.txt");
    srand(time(0));
    
    load_data();

    load_player_data();
    play_game();

    return 0;
}

bool is_only() //check if more than 1 people are still in the game (not bankrupt)
{
    int cnt = 0;

    for(int i = 0; i < 4; i++)
        if(Game::person[i].get_balance() >= 0)
            cnt++;

    return cnt <= 1;
}


//main logic
void play_game()
{
    while(!is_only()) //loop until only 1 player left
    {
        for(int i = 0; i < 4 && !is_only(); i++) // for each player, first check if that player is the only one left
        {
            //player stats
            Player &currentPlayer = Game::person[i]; //call by reference

            //check if current player is bankrupt
            if(currentPlayer.get_balance() < 0) continue;


            //display
            Display::display_player(currentPlayer.get_name(), currentPlayer.get_balance());
            
            //roll dice
            int roll1,roll2;
            do
            {
                currentPlayer.roll_dice(roll1, roll2);
                
                Display::display_event(currentPlayer.get_name() + " Rolled a " + to_string(roll1) + " and a " + to_string(roll2)
                + ((roll1 == roll2) ? "..double!!!!":""));

                currentPlayer.set_position(currentPlayer.get_position() + roll1 + roll2); //walk
                
            } while (roll1 == roll2);
            
            //check if pass go
            if(currentPlayer.get_position() > Game::board.size() - 1)
            {
                while(currentPlayer.get_position() > Game::board.size() - 1) 
                    currentPlayer.set_position(currentPlayer.get_position() - (Game::board.size() - 1)); //segmentation fault prevention.
        
                Display::display_event(
                    currentPlayer.get_name() + " has passed go $200 has been granted to the player!"
                );
                
                
                currentPlayer.set_balance(currentPlayer.get_balance() + 200); //update balance
                Display::display_event("You now have: $" + to_string(currentPlayer.get_balance()));


            }

            
            //get data of the tile of the player's current position.

            Tile* currentTile = Game::board[currentPlayer.get_position()];


            Display::display_tile(currentPlayer.get_name(), currentPlayer.get_position(),
                                  currentTile -> get_name(), currentTile -> get_description());

            //case handling
            if(Property *p = dynamic_cast<Property*>(currentTile))
                p -> tick_property(currentPlayer);

            else if (Station *s = dynamic_cast<Station*>(currentTile))
            {
                s -> tick_station(currentPlayer);
            }
            if(Tax *t = dynamic_cast<Tax*>(currentTile))
                t -> tick_tax(currentPlayer);

            else if (Misc *m = dynamic_cast<Misc*>(currentTile))
            {
                m -> tick_misc(currentPlayer);
            }
            
            //check if bankrupt
            if(currentPlayer.get_balance() < 0)
                file_for_bankruptcy(currentPlayer);
        }
    }

    cout << "WE HAVE A WINNERRRR!!!!!!" << endl;
}

//takes player who has gone bankrupt
//give all his property away.
void file_for_bankruptcy(Player &p)
{
    Tile *t = Game::board[p.get_position()];
    string newOwner = t -> get_owner();

    Display::display_event(p.get_name() + " has gone bankrupt. " + newOwner + " will inherit all of " + p.get_name() + "'s property.");

    for(auto &u : Game::board)
    {
 
        if(u -> get_owner() == p.get_name())
        {
            u -> set_owner(newOwner);
            Display::display_event(newOwner + " has inherited " + u -> get_name());
        }
    }
}


//gets player information
void load_player_data()
{
    int humans;
    cout << "How many human players are there (4 max)? "; cin >> humans;
    humans = min(humans, 4);

    string dummy; getline(cin, dummy); //flush newline char

    for(int i = 0; i < 4; i++)
    {
        string name;
        Player p; 
        if(i < humans)
        {
            cout << "Hello Player" << i+1 << ". What name do you want to go by? "; getline(cin, name);
            p.init(name, STARTING_MONEY, 0, 0, 0);
        }
        else
        {
            name = "BOT#" + to_string(i+1 - humans);
            p.init(name, STARTING_MONEY, 0, 1, rand() % 50 + 50);
        }
        
        
        Game::person[i] = p;
    }
}

//reads game data into the data structs in namespace Game
void load_data()
{
    ifstream fin(DATA);
    
    string type, name, description, owner;
    int fee, ownerCost, houseCost, houseMulti, limit, rate;

    for(;!fin.eof();) //until end of file.
    {
        while(true)
        {
            string label; fin >> label; //label determines what variable to read into
            //cout << label << endl;
            if(label == "END") break;

            else if(label == "Type:") fin >> type;
            else if(label == "Name:") fin >> name;
            else if(label == "Description:") fin >> description; 
            else if(label == "Fee:") fin >> fee;
            

            else if(label == "Owner:") fin >> owner; 
            else if(label == "OwnerCost:") fin >> ownerCost;
            else if(label == "HouseCost:") fin >> houseCost;
            else if(label == "HouseMulti:") fin >> houseMulti;
            else if(label == "Limit:") fin >> limit;
            else if(label == "Rate:") fin >> rate;
            
        }
        if(type == "Property") //init tile with property inheritance
        {
            Property* p = new Property(type, name, description, owner, 
                    fee, ownerCost, houseCost, houseMulti, limit);

            //cout << houseMulti << endl;

            Game::board.push_back(p);
        }
        else if(type == "Station") //tile with station inheritance
        {
            Station* s = new Station(type, name, description, owner, ownerCost);
            Game::board.push_back(s);
        }
        else if(type == "Tax") //tax inheritance
        {
            Tax* t = new Tax(type, name, description, rate);
            Game::board.push_back(t);
        }
        else if(type == "Misc") //misc inheritance
        { 
            Misc* m = new Misc(type, name, description, fee);
            Game::board.push_back(m);
        }
    }
}

//class definitions -----------------------------------------------------------------------------------------------------------------


//player class method definitions
void Player::init(string name, int balance, int position, int type, int weight) //intializing variables
{
    m_name = name;
    m_balance = balance;
    m_position = position;
    m_type = type;

    m_weight = weight;
}
string Player::get_name() const //returns player name
{
    return m_name;
}
int Player::get_balance() const //returns player balance
{
    return m_balance;
}
int Player::get_position() const //returns player position
{
    return m_position;
}
int Player::get_type() const //returns player type (human or computer);
{
    return m_type;
}

void Player::set_balance(int amount) //set player balance
{
    m_balance = amount;
}
void Player::set_position(int position) //set player position
{
    m_position = position;
}

void Player::roll_dice(int &a, int &b) //roll the dice, store result in the call-by-reference ints
{
    a = rand() % 6 + 1;
    b = rand() % 6 + 1;
}

//Tile class method definitions
string Tile::get_name() const //return tile name
{
    return m_name;
}
string Tile::get_description() const //returns tile description
{
    return m_description;
}
string Tile::get_type() const //returns tile type (Property, station, tax, misc)
{
    return m_type;
}

//property class method definitions
void Property::tick_property(Player &p) //called everytime a player lands on a property tile, does buy house, buy property, pay rent. Chances p's balance
{
    //check ownership
    if(m_owner == "~")
    {
        //unowned
        Display::display_event("The property is available, do you wish to buy it? (y/n)\nCost: " + to_string(m_ownerCost) + "\n");
        
        
        //check if computer or humanm then make the corresponding decisions
        string answer;
        if(p.get_type() == 0) cin >> answer;
        else answer = p.make_property_decision(m_ownerCost);
        

        if(answer == "y")
        {
            if(m_ownerCost > p.get_balance()) //check if can buy
            {
                Display::display_event("Sorry " + p.get_name() +", You do not have sufficient funds.");
                return;
            }

            //update
            p.set_balance(p.get_balance() - m_ownerCost); //chance balance
            Display::display_event("$" + to_string(m_ownerCost) + " has been deducted from your account");
            Display::display_event("You now have: $" + to_string(p.get_balance()));
            m_owner = p.get_name(); //assign ownership
        }
    }
    else if(p.get_name() == m_owner)
    {
        //revisit...buy house
        Display::display_event("Weclome back owner. Do you wish to buy a house? (y/n)\nCost: " + to_string(m_houseCost));
        
        //check if computer or humanm then make the corresponding decisions
        string answer;
        if(p.get_type() == 0) cin >> answer;
        else answer = p.make_house_decision();


        if(answer == "y")
        {
            if(m_houseCost > p.get_balance()) //can't buy
            {
                Display::display_event("You have insufficient funds to start construction");
                return;
            }
            else if(m_fee / m_houseCost >= m_limit) //max buildings
            {
                Display::display_event("You have maxed out the buildings in this location");
                return;
            }
            else //buy buildings
            {
                Display::display_event("How many houses do you wish to buy?\nyou have owned: "
                                       + to_string(m_fee / m_houseCost) + "/" + to_string(m_limit) + "\n");
                
                
                //check if computer or humanm then make the corresponding decisions
                int num;
                if(p.get_type() == 0) cin >> num;
                else num = p.how_many_house();
                
                num = min(num, m_limit - m_fee / m_houseCost); //prevent overflow
                
                while (num * m_houseCost > p.get_balance())
                {
                    Display::display_event("You don't have the sufficient funds to buy this...reducing number of houses by 1");
                    num--;
                }
                
                //update
                p.set_balance(p.get_balance() - num * m_houseCost); //update player balance
                m_fee += num * m_houseMulti; //update rent
                Display::display_event(to_string(num * m_houseCost) + " has been deducted");
                Display::display_event("You now have: $" + to_string(p.get_balance()));
            }
            
        }
    }
    else
    {
        //pay rent
        Display::display_event("This tile is owned by: " + m_owner + ", " + to_string(m_fee) + " has been deducted from your account");
        p.set_balance(p.get_balance() - m_fee);
        Display::display_event("You now have: $" + to_string(p.get_balance()));

        //give to owner
        for(int i = 0; i < 4; i++)
        {
            if(Game::person[i].get_name() == m_owner) //find account of property owner;
            {
                Game::person[i].set_balance(Game::person[i].get_balance() + m_fee);
            }
        }


    }
    
}
string Property::get_owner() //returns owner
{
    return m_owner;
}
void Property::set_owner(string owner) //sets owner
{
    m_owner = owner;
}
//station method defintions
void Station::tick_station(Player& p) //calls this when player lands on station tile. Checks ownership, sells, or applies rent.
{
    if(p.get_name() == m_owner)
    {
        //do nothing
        Display::display_event("Welcome back to your own train station.");
    }
    else if(m_owner == "~")
    {
        //buy
        Display::display_event("The property is available, do you wish to buy it? (y/n)\nCost: " + to_string(m_ownerCost) + "\n");
        
        string answer;
        if(p.get_type() == 0)cin >> answer;
        else answer = p.make_property_decision(m_ownerCost);
    
        if(answer == "y")
        {
            if(m_ownerCost > p.get_balance())
            {
                Display::display_event("Sorry " + p.get_name() +", You do not have sufficient funds.");
                return;
            }
            p.set_balance(p.get_balance() - m_ownerCost);
            Display::display_event("$" + to_string(m_ownerCost) + " has been deducted from your account");
            Display::display_event("You now have: $" + to_string(p.get_balance()));

            m_owner = p.get_name();
        }
    }
    else
    {
        //pay rent
        Display::display_event("This station is owned by: " + m_owner + ", " + to_string(m_ownerCost) + " has been deducted from your account");
        p.set_balance(p.get_balance() - m_ownerCost);
        Display::display_event("You now have: $" + to_string(p.get_balance()));

        //give to owner
        for(int i = 0; i < 4; i++)
        {
            if(Game::person[i].get_name() == m_owner)
            {
                Game::person[i].set_balance(Game::person[i].get_balance() + m_ownerCost);
            }
        }
    }
}
string Station::get_owner() //return owner of station
{
    return m_owner;
}
void Station::set_owner(string owner) //set the owner of station.
{
    m_owner = owner;
}

//tax method definitions
void Tax::tick_tax(Player& p) //takes Class Player and applies income tax rate
{
    Display::display_event("You need to pay a tax with rate: " + to_string(m_rate) + "%"); //display

    int taxDue = (double) p.get_balance() * ((double) m_rate / 100.0); //calculate amt due
    Display::display_event("...." + to_string(taxDue));

    p.set_balance(p.get_balance() - taxDue); //update
    Display::display_event("You now have: $" + to_string(p.get_balance()));
}

//misc method definitions
void Misc::tick_misc(Player& p) //just updates player balance when needed
{
    if(p.get_position() == 0) // go already processed
        return;
    
    if(m_fee != 0)
    {
        Display::display_event("Your balance was changed by: " + to_string(m_fee));
        Display::display_event("Your balance is now: $ " + to_string(p.get_balance()));
    }
}


//class costructor definitions;
Property::Property(string type, string name, string description, string owner, 
                    int fee, int ownerCost, int houseCost, int houseMulti, int limit)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_owner = owner;
    m_fee = fee;
    m_ownerCost = ownerCost;
    m_houseCost= houseCost;
    m_houseMulti = houseMulti;
    m_limit = limit;
}


Station::Station(string type, string name, string description, string owner, int ownerCost)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_owner = owner;
    m_ownerCost = ownerCost;
}

Tax::Tax(string type, string name, string description, int rate)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_rate = rate;
}
Misc::Misc(string type, string name, string description, int fee)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_fee = fee;
}