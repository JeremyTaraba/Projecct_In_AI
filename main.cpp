using namespace std;
#include "prompt.h"

//all main does it call the correct functions

int main(){

    int puzzleType;
    puzzleType = prompt();
    cout << "Puzzle Type: " << puzzleType << endl;

    return 0;
}