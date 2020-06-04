#ifndef ALROGITHM_H_
#define ALGORITHM_H_

#include <vector>
#include <queue>
#include <functional>

using namespace std;

//we really onlt need the generalAlgorithm in this header since nothing else is called outside of this cpp

bool generalAlgorithm(vector<int>, int);
bool goalChecker(vector<int>, vector<int>);
bool exploredChecker(vector<int>, vector<vector<int>>);
int findLocationOfZero(vector<int>);
vector<int> findMoves(int zeroLocation, int puzzleSize);
vector<int> possibleStates(vector<int>, vector<int>, int, int);


#endif