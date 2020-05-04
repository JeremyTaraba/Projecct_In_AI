#include "uniformCost.h"
#include "linkedList.h"
#include <iostream>
#include <vector>

using namespace std;


bool uniformCostSearch(vector<int> puzzle){
    linkedList *root = createNode(puzzle, 0);
    //frontier = prioirity queue ordered by path cost with initialNode as the only element
    //explored = empty set

    //loop 
        //if frontier empty then return failure
        //pop frontier (lowest node cost in frontier is popped)
        //if node.state = solution then return solution
        //add node.state to explored

        //for each action you can do in the current state
            //child = child.node(problem,node,action)
            //if child.state is not in explored or frontier
                //frontier insert child into appropriate position
            //else if child.state is in frontier with higher cost
                //replace that frontier node with child

    return true;
}

int finalOutput(){

    return 0;
}