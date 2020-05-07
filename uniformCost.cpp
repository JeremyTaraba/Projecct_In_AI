#include "uniformCost.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;


//creates operator overloading for priority_queue
struct compare { 
    bool operator()(linkedList *lhs, linkedList *rhs) 
    { 
        // returns true where top of queue is less than what is under it
        return lhs->cost > rhs->cost;
    } 
}; 


const int LEFT = 0;
const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;

int costFunction(linkedList*);
int frontierCost(vector<int>, priority_queue <linkedList*, vector<linkedList*>, compare>);
vector<int> frontierCheckerAndCost(vector<int> nextState, priority_queue<linkedList*, vector<linkedList*>, compare> frontier);
bool frontierChecker(vector<int>, priority_queue<linkedList*, vector<linkedList*>, compare>);


bool uniformCostSearch(vector<int> puzzle){
    linkedList *curNode = createNode(puzzle, 0, NULL); //initial state with cost = 0 and parent = NULL

    //min cost queue
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  

    //keep track of past puzzle states so we dont revisit them
    vector<vector<int>> explored;   

     //generate goal state based on differing sizes of puzzles
     vector<int> goal;
     for(int i = 0; i < puzzle.size(); i++){
         if(i == puzzle.size() - 1){
            goal.push_back(0);
         }
         else{
            goal.push_back(i+1);
         }
     }


     frontier.push(curNode);
     linkedList *parentNode = NULL;
     linkedList *childNode;
     int identicalFrontierCost;
     vector<int> possibleMoves;
     vector<int> nextState;
     int locationOfZero;
     bool inFrontier;
     bool inExplored;
     int nodeCost;

     //first iteration of while loop creates a copy of root node.
     //should create a deallocator function and manually delete root node so no leaks

    while(1){
        if(frontier.empty()){
            cout <<"frontier is empty" << endl;
            return false;
        }
        curNode = createNode(frontier.top()->state, 0, parentNode);

        //testing//
        cout << endl;
        cout << "printing out curNode: " << endl;
        for(int i = 0; i < curNode->state.size(); i++){
            cout << curNode->state.at(i) << " ";
        }
        cout << endl << endl;
        //testing//

        frontier.pop();
        if(goalChecker(curNode->state, goal)){
            return true;
        }
        explored.push_back(curNode->state);
        locationOfZero = findLocationOfZero(curNode->state);
        possibleMoves = findMoves(locationOfZero, curNode->state.size());
        parentNode = curNode;
        for(int i = 0; i < possibleMoves.size(); i++){
            nextState = possibleStates(curNode->state, possibleMoves, i, locationOfZero); //one of the next states we can create 


                //testing//
            cout << endl;
            cout << "# of possible moves: " << possibleMoves.size() << endl;
            cout << "specific move for i: " << possibleMoves.at(i) << "   ";
            cout << "printing out nextState: ";
            for(int i = 0; i < curNode->state.size(); i++){
                cout << curNode->state.at(i) << " ";
            }
            cout << endl << endl;
            //testing//

            inFrontier = frontierChecker(nextState, frontier); 
            inExplored = exploredChecker(nextState, explored);
            if(!inFrontier && !inExplored){   //if child node is not in frontier and not in explored
                nodeCost = costFunction(parentNode);
                childNode = createNode(nextState, nodeCost, parentNode);
                frontier.push(childNode);
                curNode->next = childNode;
            }
            else if(inFrontier){     //else if in frontier but the one in frontier has a higher path cost then replace it with this childNode
                nodeCost = costFunction(parentNode);
                identicalFrontierCost = frontierCost(nextState, frontier);
                if(nodeCost < identicalFrontierCost){
                    childNode = createNode(nextState, nodeCost, parentNode);
                    //swap frontier node with childNode
                    curNode->next = childNode;
                }
            }
           
        }
    }

    //never reached
    return true;
}

//distance from initial state
int costFunction(linkedList *parentNode ){
    return parentNode->cost + 1;
}

vector<int> possibleStates(vector<int> puzzle, vector<int> possibleMoves, int index, int locationOfZero){
    int indexOfZero = locationOfZero - 1;
    int blankSpace;
    int swapValue;
    vector<int> changedPuzzle = puzzle;

    switch(possibleMoves.at(index)){    //checking if we move left, right, up, or down next
        case 0:     //case for moving 0 left
            blankSpace = changedPuzzle.at(indexOfZero);
            swapValue = changedPuzzle.at(indexOfZero - 1);
            changedPuzzle.at(indexOfZero) = swapValue;
            changedPuzzle.at(indexOfZero - 1) = blankSpace;
            cout << "outputting changed puzzle: ";
            for(int i = 0; i < changedPuzzle.size(); i++){
                cout << changedPuzzle.at(i) << " ";
            }
            cout << endl;
            break;
        case 1:     //case for moving zero up
            blankSpace = changedPuzzle.at(indexOfZero);
            swapValue = changedPuzzle.at(indexOfZero - sqrt(changedPuzzle.size()));
            changedPuzzle.at(indexOfZero) = swapValue;
            changedPuzzle.at(indexOfZero - sqrt(changedPuzzle.size())) = blankSpace;
            break;
        case 2:     //case for moving zero right
            blankSpace = changedPuzzle.at(indexOfZero);
            swapValue = changedPuzzle.at(indexOfZero + 1);
            changedPuzzle.at(indexOfZero) = swapValue;
            changedPuzzle.at(indexOfZero + 1) = blankSpace;
            break;
        case 3:     //case for moving zero down
            blankSpace = changedPuzzle.at(indexOfZero);
            swapValue = changedPuzzle.at(indexOfZero + sqrt(changedPuzzle.size()));
            changedPuzzle.at(indexOfZero) = swapValue;
            changedPuzzle.at(indexOfZero + sqrt(changedPuzzle.size())) = blankSpace;
            break;
        default:
            cout << "error!" << endl;
    }

    return changedPuzzle;
}

void finalOutput(int expandNodes, int queueNodes){
    cout << "goal!" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << expandNodes << " nodes" << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << queueNodes << endl;
}

bool exploredChecker(vector<int> curNode, vector<vector<int>> explored){
    int exploreCounter = 0;     //keeps track of how many puzzles we checked

    for(int i = 0; i < explored.size(); i++){
        for(int j = 0; j < explored.at(i).size(); j++){
            if(curNode.at(j) != explored.at(i).at(j)){
                exploreCounter++;
                break;
            }
        }
    }

    //we went through all puzzles in explored. if not equal then we had a match so return true
    return exploreCounter != explored.size();
}

bool frontierChecker(vector<int> nextState, priority_queue<linkedList*, vector<linkedList*>, compare> frontier){    //check that frontier doesnt get mess up when returned
    vector<int> inFrontier = frontierCheckerAndCost(nextState, frontier);
    return inFrontier.at(0);
}

int frontierCost(vector<int> nextState, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    vector<int> cost = frontierCheckerAndCost(nextState, frontier);
    return cost.at(1);
}

vector<int> frontierCheckerAndCost(vector<int> nextState, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    int countNotEqual = 0;
    vector<int> inFrontierAndCost;
    int sameStateCost;

    vector<int> frontierState;
    for(int i = 0; i < frontier.size(); i++){
        frontierState = frontier.top()->state;
        for(int j = 0; j < frontierState.size(); j++){
            if(nextState.at(j) != frontierState.at(j)){
                countNotEqual++;
                break;
            }
        }
        if(i != countNotEqual-1){
            sameStateCost = frontier.top()->cost;
            break;
        }
        frontier.pop();       
    }

    //if counter is not the same as frontier.size() then there was a match somewhere
    if(countNotEqual != frontier.size()){
        inFrontierAndCost.push_back(1);
    }
    else{
        inFrontierAndCost.push_back(0);
    }
    inFrontierAndCost.push_back(sameStateCost);

    return inFrontierAndCost;
}

//could use pass by reference here
priority_queue <linkedList*, vector<linkedList*>, compare> replaceFrontierElement(linkedList *childNode, priority_queue <linkedList*, vector<linkedList*>, compare> frontier){
    priority_queue <linkedList*, vector<linkedList*>, compare> changedFrontier;
    vector<int> nextState = childNode->state;

    int countNotEqual = 0;
    vector<int> frontierState;
    for(int i = 0; i < frontier.size(); i++){
        frontierState = frontier.top()->state;
        for(int j = 0; j < frontierState.size(); j++){
            if(nextState.at(j) != frontierState.at(j)){
                countNotEqual++;
                break;
            }
        }
        if(i != countNotEqual-1){
            frontier.pop();
        }
        else{
            changedFrontier.push(frontier.top());
            frontier.pop();
        }       
    }
    changedFrontier.push(childNode);


    return changedFrontier;
}


bool goalChecker(vector<int> puzzle, vector<int> goal){
    bool goalReached = true;
    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle.at(i) != goal.at(i)){
            goalReached = false;
            break;
        }
    }
    return goalReached;
}

int findLocationOfZero(vector<int> puzzle){
    int moveCase = 1;

    for(int i = 0; i < puzzle.size(); i++){
        if(puzzle.at(i) == 0){
            break;
        }
        moveCase++;
    }

    return moveCase;
}

vector<int> findMoves(int zeroLocation, int puzzleSize){
    vector<int> possibleMoves;

    if(zeroLocation == 1){          //means if 0 is in top left corner
        possibleMoves.push_back(RIGHT);
        possibleMoves.push_back(DOWN);
    }
    else if(zeroLocation == puzzleSize){       //if 0 is in bottom right corner
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(UP);
    }
    else if(zeroLocation == sqrt(puzzleSize)){     //if 0 is at the end of the first row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
    }
    else if( (zeroLocation > 1) && (zeroLocation < sqrt(puzzleSize)) ){     //if 0 is between the top left corner and end of first row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
        possibleMoves.push_back(RIGHT);
    }
    else if(zeroLocation == (puzzleSize - sqrt(puzzleSize)) ){     //if 0 is at the start of the last row
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(DOWN);
    }
    else if( (zeroLocation > (puzzleSize - sqrt(puzzleSize)) ) && (zeroLocation < puzzleSize) ){     //if 0 is between the bottom right corner and bottom left corner
        possibleMoves.push_back(LEFT);
        possibleMoves.push_back(UP);
        possibleMoves.push_back(RIGHT);
    }
    else{   //zero is not in the first or last rows and is somewhere in the rows between
        for(int i = 1; i < (1-sqrt(puzzleSize)); i++){
            if(zeroLocation == (i*sqrt(puzzleSize) + 1) ){    //if 0 is start of a row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
                break;
            }
            else if(zeroLocation == ((i+1)*sqrt(puzzleSize)) ){   //if 0 is end of a row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(DOWN);
            }
            else if(zeroLocation > (i*sqrt(puzzleSize) + 1) && zeroLocation < ((i+1)*sqrt(puzzleSize))){    //if 0 is between start and end of row
                possibleMoves.push_back(UP);
                possibleMoves.push_back(LEFT);
                possibleMoves.push_back(RIGHT);
                possibleMoves.push_back(DOWN);
            }
        }
    }
    

    return possibleMoves;
}


/*

int main(){
    vector<int> puzzle = {1,2,3,4,5,6,7,8,0};
    vector<int> puzzle2 = {0,2,3,4,5,6,7,8,1};

    vector<vector<int>> explored;      

    linkedList* curNode = createNode(puzzle, 5, NULL);
    linkedList* curNode2 = createNode(puzzle2, 7, NULL);
    linkedList* curNode3 = createNode(puzzle, 3, NULL);
    linkedList* curNode4 = createNode(puzzle2, 4, NULL);
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  
    frontier.push(curNode);
    frontier.push(curNode2);
    

    

    cout << "test frontierChecker for return false: ";
    if(frontierChecker(curNode2->state, frontier)){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }


    cout << "test frontierCost is 5: ";
    cout << frontierCost(curNode3->state, frontier) << endl;

   
    cout << "test frontierChecker for return true: ";
    if(frontierChecker(curNode3->state, frontier)){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
    frontier.push(curNode3);



    
    frontier = replaceFrontierElement(curNode4, frontier);




    cout << "top = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "next = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "last = " << frontier.top()->cost << endl;

    explored.push_back(curNode->state);
    if(exploredChecker(curNode2->state, explored)){
        cout << "we explored puzzle2 already" << endl;
    }
    else{
        cout << "we have -not- explored puzzle2 already" << endl;
    }
    if(exploredChecker(curNode3->state, explored)){
        cout << "we explored puzzle already" << endl;
    }
    else{
        cout << "we have -not- explored puzzle already" << endl;
    }

    cout << "location of zero should be 9: " << findLocationOfZero(curNode->state) << endl;
   
    vector<int> a = findMoves(findLocationOfZero(curNode->state), curNode->state.size());
    cout << "size of a should be 2: " << a.size() << endl;
    cout << "moves for zero should be Left(0) and Up(1): ";
    for(int i = 0; i < a.size(); i++){
        cout << a.at(i) << " ";
    }
    cout << endl;

    vector<int> b = possibleStates(curNode->state, a, 0, 9);
    linkedList *childNode = createNode(b, 0, NULL);
    if(goalChecker(childNode->state, puzzle)){
        cout << "Goal!!" << endl;
    }
    else{
        cout << "no goal" << endl;
    }


    if(goalChecker(curNode->state, puzzle)){
        cout << "Goal!!" << endl;
    }
    else{
        cout << "no goal" << endl;
    }



    return 0;
} */