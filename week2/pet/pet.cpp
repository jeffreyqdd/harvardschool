#include <iostream>
using namespace std;


int main()
{
    int numPets;

    cout << "How many pets do you have? ";
    cin >> numPets;


    switch(numPets)
    {
        case 0:
            cout << "Do you like aninals\n";
            break;
        case 1:
        case 2:
            cout << "One or two pets can keep you company\n";
            break;
        case 3:
        case 4:
        case 5:
            cout << "Thank you\n";
            break;
        default:
            cout << "Are you running a zoo?\n";
            break;
    }
    /*
    if(numPets < 0) cout << "How can you have negative pets?\n";
    else if(!numPets) cout << "Do you like animals\n";
    else if(numPets <= 2) cout << "One or two pets can keep you company\n";
    else if(numPets < 5) cout << "Thank you\n";
    else cout << "Do you have a zoo? \n";
    */

    return 0;
}
