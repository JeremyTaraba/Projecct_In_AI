#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

struct point {
    int class;
    vector<int> features;  
};

//Create nearest neighbor classifier (keep training data in memory and when new data point is given classify it)
//need to normalize the untis. Do this by Feature1 = (feature1_value - mean(feature1)) / stddev(feature1)
//Find the distance with dist between point1 and point2 = sqrt( pow(2,point1(feature1) - point2(feature1)) )

int nearestNeighborClassifier(){




}




//Create Leave one out validator (need training data and the classifier)


//Create Forward search algorithm (adds or removes features and assigns accuracy score to the combinations and chooses highest one)


int main(){


    return 0;
}