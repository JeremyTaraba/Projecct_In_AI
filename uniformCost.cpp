#include "uniformCost.h"
#include "linkedList.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//creates operator overloading for priority_queue
struct compare { 
    bool operator()(linkedList *lhs, linkedList *rhs) 
    { 
        // returns true where top of queue is less than what is under it
        return lhs->cost > rhs->cost;
    } 
}; 


bool uniformCostSearch(vector<int> puzzle){
    linkedList *curNode = createNode(puzzle, 0, NULL); //initial state with cost = 0 and parent = NULL

    //min cost queue
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  

    //keep track of past puzzle states so we dont revisit them
    vector<int> explored;   

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

    // while(1){
    //     if(frontier.empty()){
    //         return false;
    //     }
    //     curNode = createNode(frontier.top(), 0, parentNode);
    //     frontier.pop();
    //     if(goalChecker(curNode, goal)){
    //         return true;
    //     }
    //     explored.push(curNode);
    //     for(//each different move we can do based on 0){
    //         childNode = ;//one of the next actions we can do
    //         //for loop to check if child node is in frontier or if it is in explored
    //         //else frontier.push(childNode);
    //         //else if in frontier but the one in frontier has a higher path cost then replace it with this childNode
    //     }



    // }

    return true;
}

void finalOutput(int expandNodes, int queueNodes){
    cout << "goal!" << endl;
    cout << "To solve this problem the search algorithm expanded a total of " << expandNodes << " nodes" << endl;
    cout << "The maximum number of nodes in the queue at any one time: " << queueNodes << endl;

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

int main(){
    vector<int> puzzle = {1,2,3,4,5,6,7,8,0};

    linkedList* curNode = createNode(puzzle, 5, NULL);
    linkedList* curNode2 = createNode(puzzle, 7, NULL);
    linkedList* curNode3 = createNode(puzzle, 3, NULL);
    priority_queue <linkedList*, vector<linkedList*>, compare> frontier;  
    frontier.push(curNode);
    frontier.push(curNode2);
    frontier.push(curNode3);
    cout << "top = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "next = " << frontier.top()->cost << endl;
    frontier.pop();
    cout << "last = " << frontier.top()->cost << endl;

    if(goalChecker(curNode->state, puzzle)){
        cout << "Goal!!" << endl;
    }



    return 0;
}