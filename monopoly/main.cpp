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
void play_game()
{
    while(true) //loop infinitely
    {
        for(int i = 0; i < 4; i++) // for each player
        {
            //player stats
            Player &currentPlayer = Game::person[i]; //call by reference
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
                currentPlayer.set_position(currentPlayer.get_position() - Game::board.size());
        
                Display::display_event(
                    currentPlayer.get_name() + " has passed go $200 has been granted to the player!"
                );

                currentPlayer.set_balance(currentPlayer.get_balance() + 200);
            }

            

            Tile* currentTile = Game::board[currentPlayer.get_position()];


            Display::display_tile(currentPlayer.get_name(), currentPlayer.get_position(),
                                  currentTile -> get_name(), currentTile -> get_description());

            //case handling
            if(Property *p = dynamic_cast<Property*>(currentTile))
                p -> tick_property(currentPlayer);

            else if (Station *p = dynamic_cast<Station*>(currentTile))
            {
                p -> tick_station(currentPlayer);
            }
            


            
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
        if(i < humans)
        {
            cout << "Hello Player" << i+1 << ". What name do you want to go by? "; getline(cin, name);
        }
        else
        {
            name = "BOT#" + to_string(i+1 - humans);
        }
        
        Player p; p.init(name, STARTING_MONEY, 0, 0);
        Game::person[i] = p;
    }
}

//reads game data into the data structs in namespace Game
void load_data()
{
    ifstream fin(DATA);
    
    string type, name, description, owner;
    int fee, ownerCost, houseCost, houseMulti, limit, rate;

    for(;!fin.eof();)
    {
        while(true)
        {
            string label; fin >> label;
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
        if(type == "Property")
        {
            Property* p = new Property(type, name, description, owner, 
                    fee, ownerCost, houseCost, houseMulti, limit);

            Game::board.push_back(p);
        }
        else if(type == "Station")
        {
            Station* s = new Station(type, name, description, owner, ownerCost);
            Game::board.push_back(s);
        }
        else if(type == "Tax")
        {
            Tax* t = new Tax(type, name, description, rate);
            Game::board.push_back(t);
        }
        else if(type == "Misc")
        { 
            Misc* m = new Misc(type, name, description, fee);
            Game::board.push_back(m);
        }
    }
}



//player class method definitions
void Player::init(string name, int balance, int position, int type) //intializing variables
{
    m_name = name;
    m_balance = balance;
    m_position = position;
    m_type = type;
}
string Player::get_name() const
{
    return m_name;
}
int Player::get_balance() const
{
    return m_balance;
}
int Player::get_position() const
{
    return m_position;
}
int Player::get_type() const
{
    return m_type;
}

void Player::set_balance(int amount)
{
    m_balance = amount;
}
void Player::set_position(int position)
{
    m_position = position;
}

void Player::roll_dice(int &a, int &b)
{
    a = rand() % 6 + 1;
    b = rand() % 6 + 1;
}

//Tile class method definitions
void Tile::dummy_function() {}

string Tile::get_name() const
{
    return m_name;
}
string Tile::get_description() const
{
    return m_description;
}
string Tile::get_type() const
{
    return m_type;
}


//property class method definitions


void Property::tick_property(Player &p)
{
    //check ownership
    if(m_owner == "~")
    {
        string answer;
        //unowned
        Display::display_event("The property is available, do you wish to buy it? (y/n)\nCost: " + to_string(m_ownerCost) + "\n");
        cin >> answer;

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
    else if(p.get_name() == m_owner)
    {
        //revisit
        string answer;
        Display::display_event("Weclome back owner. Do you wish to buy a house? (y/n)\nCost: " + to_string(m_houseCost));
        cin >> answer;
        if(answer == "y")
        {
            if(m_houseCost > p.get_balance())
            {
                Display::display_event("You have insufficient funds to start construction");
                return;
            }
            else if(m_fee / m_houseCost >= m_limit)
            {
                Display::display_event("You have maxed out the buildings in this location");
                return;
            }
            else
            {
                int num;
                Display::display_event("How many houses do you wish to buy?\nyou have owned: "
                                       + to_string(m_fee / m_houseCost) + "/" + to_string(m_limit) + "\n");
                
                cin >> num; num = min(num, m_limit - m_fee / m_houseCost); //prevent overflow
                
                while (num * m_houseCost > p.get_balance())
                {
                    Display::display_event("You don't have the sufficient funds to buy this...reducing number of houses by 1");
                    num--;
                }
                
                p.set_balance(p.get_balance() - num * m_houseCost);
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
            if(Game::person[i].get_name() == m_owner)
            {
                Game::person[i].set_balance(Game::person[i].get_balance() + m_fee);
            }
        }


    }
    
}

//station method defintions

void Station::tick_station(Player& p)
{
    if(p.get_name() == m_owner)
    {
        //do nothing
        Display::display_event("Welcome back to your own train station.");
    }
    else if(m_owner == "~")
    {
        //buy
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

//tax method definitions
void Tax::tick_tax(Player& p) //takes Class Player and applies income tax rate
{
    Display::display_event("You need to pay a tax with rate: " + to_string(m_rate) + "%"); //display

    int taxDue = (double) p.get_balance() * ((double) m_rate / 100.0); //calculate amt due
    Display::display_event("...." + taxDue);

    p.set_balance(p.get_balance() - taxDue); //update
    Display::display_event("You now have: $" + to_string(p.get_balance()));
}

//class Init definitions;
Property::Property(string type, string name, string description, string owner, 
                    int fee, int ownerCost, int houseCost, int houseMulti, int limit)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_owner = owner;
    m_fee = fee;
    m_ownerCost = ownerCost;
    m_houseCost = houseMulti;
    m_limit = limit;
}


Station::Station(string type, string name, string description, string owner, int ownerCost)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_owner = owner;
    ownerCost = ownerCost;
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