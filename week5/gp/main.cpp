//in file symbols
//for the things below # means numbers
//@# symbols the text for scenario #
//under each scenario, there will be choices 
//# means jump to scenario #


#include <string>
using namespace std;

#define TEXT_FILE "scenes.txt"

#include "engine.h"


//probably the shortest main code I've ever written.
int main()
{    
    You Game;

    while (Game.tick(TEXT_FILE));

    return 0;
}
