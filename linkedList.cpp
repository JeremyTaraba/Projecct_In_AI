#include "linkedList.h"
#include <vector>
#include <iostream>

using namespace std;

linkedList* createNode(vector<int> input, int pathCost){
    linkedList *node;      
    
    node = new linkedList; 
    node->next = 0;  
    node->cost = pathCost;
    node->state = input;
     
    return node;
}


