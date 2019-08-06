# intro
This is a C++ version of the popular board game Monopoly. It was written as the final project for the class Introduction to C++ programming. 


Monopoly by nature is a complicated game because there are many different outcomes and scenarios. Though for humans, the game becomes rather intuitive after reading the instruction manual. We are really good at improvising and following the varied directions on each chest/chance card.

When you export Monopoly from the physical world and into the coding world, it becomes a totally different story. We have to hand over the case handling to the computer and not the brain.

# In a nutshell

The goal of the game is to be the last one standing. A player does this buy sending the other players into debt aka making other players bankrupt. The player achieves this through buying properties, constructing houses over owned properties, clever money management, and a lot of luck. 

# Thought process and explanations

## Tiles
The game board consists of one type of entity: Tiles. It is true that there are many **types** of tiles, so there exists categories of Tiles:
1. Property tiles - ownable buy players, and are able to have houses constructed.
* This means the rent of the property is not static due to the fact that houses raise the rent.
2. Station tiles - railroad stations are similar to property tiles but they cannot have buildings constructed on them.
* This means the rent of this tile **is** static
3. Tax tiles - althought not great in number, these tiles still constitute part of the monopoly board
* Taxes work differently from property and station tiles. They are not ownable nor expandable. 
4. Miscellaneous tiles aka misc tiles - These tiles are scattered around the board and are numerious unique case handling is required for each misc tile. A few examples include:
* Free parking - nothing needs to be done 
* Chance cards - generate a random chance card
* Community Chest - generate a random community chest card
* Jail - these tiles need to be able to change the state of the player to *in jail*.


Hence I've used classes and class inheritance to make the code cleaner and more efficient: 


### Tile Class


                      > Derived class Property
Base class: Tile ->   > Derived class Station
                      > Derived class Tax
                      > Derived class Misc

We are storing a pointer to Tile so that we can access the derived classes using virtual function. Virtual functions allow us to take advantage of something called Polymorphism.

The one thing in common for ALL the types of tiles is a tick() function (case handling of that specific tile the player lands in)


'''cpp
virtual void tick()
{
    //case handling
}
'''

This allows the program to choose which tick function is best suited. This results in cleaner code in the main logic as the cases are handled elsewhere.


### Player Class

Base class Player ->  > Derived class Bot

The good thing of player monopoly one the computer is that bots can be generated to fill in the place of friends. This calls for a derived class Bot that has the data contained in Player but different decision making functions.

Once again using virtual, these classes can achieve polymorphism.

'''cpp
virtual string make_property_decision()
{
    //returns player decision using cin
}
virtual string make_property_decision()
{
    //returns string "y" or "n" through a series of if-else statements
}
'''

The bots in the game are not based off of AI. They contain a weight called m_botWeight, and it is randomly generated at the start.
This weight ranges from 50 to 100 closed and is fixed during the game. A bot with a lower weight is less likely to make risky decisions that take up more than m_botWeight% of its current balance.

# files and links
1. Github contains project backups: http://www.github.com/jeffreyqdd

2. Instructions are located in /text/instructions.txt
* it can also be accessed in game using the "-rule" command at the start of the game.
 



