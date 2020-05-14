#include "prompt.h"
#include "puzzleMaker.h"
#include "algorithms.h"
#include "linkedList.h"
#include <vector>
#include <iostream>
#include <chrono> 

using namespace std;

//all main does it call the correct functions

//when redoing the file heirarchy make main the top

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

    //start timer
    chrono::time_point<chrono::system_clock> start, end; 
    start = chrono::system_clock::now(); 

    //solve
    if(!generalAlgorithm(puzzleToSolve, algorithmType)){
        cout << "error failed to solve puzzle" << endl;
    }
    //end timer
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start; 
    cout << "total time: " << elapsed_seconds.count() << " seconds" << endl; 

    return 0;
}