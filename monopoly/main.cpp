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
            Display::display_player_name(currentPlayer.get_name());
            
            //roll dice
            int roll1,roll2;
            do
            {
                currentPlayer.roll_dice(roll1, roll2);
                
                Display::display_event(currentPlayer.get_name() + " Rolled a " + to_string(roll1) + " and a " + to_string(roll2)
                + ((roll1 == roll2) ? "..double!!!!":""));

                currentPlayer.set_position(currentPlayer.get_position() + roll1 + roll2); //walk
                
            } while (roll1 == roll2);
            
            //check and do tile action
            bool passGo = false;
            if(currentPlayer.get_position() > MAX_TILE_INDEX)
            {
                currentPlayer.set_position(currentPlayer.get_position() - MAX_TILE_INDEX);
                passGo = true;
            }

            Tile currentTile = Game::board[currentPlayer.get_position()];

                       
            if(passGo)
                Display::display_event(
                    currentPlayer.get_name() + " has passed go $200 has been granted to the player!"
                );

            cout << currentPlayer.get_name() << " has made it to tile " << currentPlayer.get_position() << ":\n\n"
                 << currentTile << endl;
 
            switch(currentTile.get_type())
            {
                case "Property":
                    property_case();
                    break;
                case "Station":
                    station_case();
                case ""
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

    for(int i = 0; i < MAX_TILE_INDEX; i++)
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
            Property p; p.init(type, name, description, owner, 
                    fee, ownerCost, houseCost, houseMulti, limit);
            Game::board[i] = p;
        }
        else if(type == "Station")
        {
            Station s; s.init(type, name, description, owner, ownerCost);
            Game::board[i] = s;
        }
        else if(type == "Tax")
        {
            Tax t; t.init(type, name, description, rate);
            Game::board[i] = t;
        }
        else if(type == "Misc")
        { 
            Misc m; m.init(type, name, description, fee);
            Game::board[i] = m;
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

//class Init definitions;
void Property::init(string type, string name, string description, string owner, 
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

void Station::init(string type, string name, string description, string owner, int ownerCost)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_owner = owner;
    ownerCost = ownerCost;
}
void Tax::init(string type, string name, string description, int rate)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_rate = rate;
}
void Misc::init(string type, string name, string description, int fee)
{
    m_type = type;
    m_name = name;
    m_description = description;
    m_fee = fee;
}