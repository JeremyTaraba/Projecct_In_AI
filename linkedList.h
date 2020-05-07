#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <vector>

using namespace std;

struct linkedList {
    int cost;
    int hn;
    int gn;
    vector<int> state;
    linkedList *next;
    linkedList *prev;
}; 

linkedList* createNode(vector<int>, int, int);
void setNext(linkedList*, linkedList*);



#endif