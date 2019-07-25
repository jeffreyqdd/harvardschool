#include "cpu.h"
#include "graphics.h"
#include "gamerule.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//commands
namespace UserInputs{
    vector<string> commands = { "-rules",
                                "-play",
                                "-reload",
                                "-quit" };
    
}

/*  Some housekeeping. Constants to keep througout the whole program: meanings of symbols and tile type.

    // ! = null, ~ not yet assigned

    //0 property
    //1 Community_Chest
    //2 Chance
    //3 Jail
    //4 misc
    //5 tax
    //6 railroads

    [[index] [name] [description] [type] [fees] [owner] [ownership cost] [house cost] [house multiplier] [limit]
*/

//keeps individual statistics regarding each tile on the monopoly board
//has a variety of functions that encompass all types of tiles.
class Tile
{
    
    int index, type, fee, ownershipCost, houseCost, houseMulti, limit;
    string name, description, ownerName;

    public:
        void init(int in, string na, string des, int ty, int fe, string ow, int oc, int hc, int hm, int li)
        {
            index = in;
            name = na;
            description = des; 
            type = ty;
            fee = fe;
            ownerName = ow;
            ownershipCost = oc;
            houseCost = hc;
            houseMulti = hm;
            limit = li;
        }
        //gets the type of tile
        int get_tile_type()
        {
            return type;
        }

        //------- The functions below all are used for property tiles;

        //check if the tile belongs to another player
        //returns owner name, if available returns ~
        string get_owner()
        {
            return ownerName;
        }

        //changes the ownership of the tile to playerName
        void allocate(const string &playerName)
        {
            ownerName = playerName;
        }
        //if the property is availale and the player wants to buy,
        //allocate propery name to player, and adjust player balance
        void buy_property(int &money, const string &playerName)
        {
            if(money < ownershipCost)
            {
                cout << "You have insufficient funds\n";
                return;
            }

            money -= ownershipCost;
            allocate(playerName);

            cout << "Transaction successful\n";
            return;
        }
        //if the player owns the property
        //check if property limit has been reached
        //change fee, and player balance
        void buy_house(int &money, const string &playerName, int quantity)
        {
            int numHouse = fee /houseMulti;
            
            if(numHouse >= 4)
            {
                cout << "Property is already full\n";
                return ;
            }
            
            //prevent overflow;
            int quanitity = min(limit - numHouse, quantity);

            

            return;
        }

        //if the tile does not belong to the player
        //subtract balance from player.
        void pay_rent_price()
        {
            
            
            return;
        }

};


void load_game()
{
    return;
}





int main()
{
    //all main is is UI.
    Graphics::display_txt("text/intro.txt");

    //matches input UI with existing commands.
    while(true)
    {
        cout << endl;
        string reply; getline(cin,reply);
        cout << endl;

        bool flag = true;
        int i = 0;
        for(i = 0; i < UserInputs::commands.size(); i++)
        {
            if(reply == UserInputs::commands[i])
            {
                flag = false;
                break;
            }
        }

        if(flag)
        {
            cout << "Invalid command\n";
            continue;
        }

        switch(i)
        {
            case 0:
                Graphics::display_txt("text/instructions.txt");
                break;
            case 1:
                cout << "generating...\n";
                load_game();
                //play();
                break;
            case 2:
                Graphics::display_txt("text/intro.txt");
                break;
            default:
                cout << "Exiting Program..\n";
                return 0;
        }
    }
    return 0;
}
