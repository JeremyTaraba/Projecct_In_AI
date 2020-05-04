#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <vector>

using namespace std;

struct linkedList {
    int cost;
    vector<int> state;
    linkedList *next;
}; 

linkedList* createNode(vector<int>, int);



#endif