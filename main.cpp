#include "prompt.h"
#include "puzzleMaker.h"
#include "uniformCost.h"
#include <vector>
#include <iostream>

using namespace std;

//all main does it call the correct functions

int main(){

    int puzzleType;
    vector<int> puzzleToSolve;
    int algorithmType;

    //prompt for puzzle type
    puzzleType = promptPuzzleType();

    //generate the puzzle based on puzzle type
    if(puzzleType == 1){
        //just outputs the default puzzle
        puzzleToSolve = puzzleMakerDefault();
    }
    if(puzzleType == 2){
        puzzleToSolve = puzzleMakerCustom();
    }

    //choose algorithm
    algorithmType = promptAlgorithmType();

    //solve
    if(algorithmType == 1){
        if(uniformCostSearch(puzzleToSolve)){
            cout << "solved the puzzle" << endl;
        }
        else{
            cout << "error" << endl;
        }
    }
    else if(algorithmType == 2){
        //do A* with missplaced tile heuristic
    }
    else if(algorithmType == 3){
        //do A* with Euclidean distance heuristic
    }



    return 0;
}