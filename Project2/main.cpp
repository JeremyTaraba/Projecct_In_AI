#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

//just for testing
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

struct point {
    int classification;
    vector<double> features;  
};


//Create nearest neighbor classifier (keep training data in memory and when new data point is given classify it)
//need to normalize the untis. Do this by Feature1 = (feature1_value - mean(feature1)) / stddev(feature1)
//Find the distance with dist between point1 and point2 = sqrt( pow(2,point1(feature1) - point2(feature1)) )

int nearestNeighborClassifier(/* Chosen_Feature_indexes, point*/){
    //first find all points (is there a better way? yes, remove instances that obviously wont be considered by sorting)
    //normalize data for point and other points
    //then calculate distances and find nearest neighbor
    //return classification

    return rand() % 2 + 1;
}




//Create Leave one out validator (need training data and the classifier)
float leaveOneOutValidator(vector<point> Data, vector<int> current_features, int feature_to_add){
    float accuracy = 0.0;
    


    return accuracy;
}


//Create Forward search algorithm (adds or removes features and assigns accuracy score to the combinations and chooses highest one)
vector<int> forwardSearchAlgorithm(vector<point> Data){
    double accuracy = 0;
    vector<int> current_set_of_features;
    

    for(int i = 0; i < Data.at(0).features.size(); i++){
        int feature_to_add;
        double best_accuracy_so_far = 0.0;
        
        for(int k = 0; k < Data.at(0).features.size(); k++){
            if(find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()){  //if k is not in current features
                accuracy = leaveOneOutValidator(Data, current_set_of_features, k);
                if(accuracy > best_accuracy_so_far){
                    best_accuracy_so_far = accuracy;
                    feature_to_add = k+1;
                }
            }   
        }
        current_set_of_features.push_back(feature_to_add);
    }
    return current_set_of_features;
}


//read the data and return a vector of points
vector<point> import_data(string filename){
    //for each line, read in data and create a data point, shove these into a vector of points
    ifstream infile;
    infile.open(filename);
    vector<point> Data;
    string line;
    double instance_feature;
    bool first_feature;
    if(infile.is_open()){
        while(getline(infile, line)){
            point instance;              //create new point
            istringstream iss(line);    //covert string to any varable type (double in this case)
            first_feature = true;
            while(iss >> instance_feature){      //read all values from the file
                if(first_feature){              //put class into classification
                    instance.classification = instance_feature;
                    first_feature = false;
                }
                else{
                    instance.features.push_back(instance_feature);  //put feature into features vector
                }
            }
            Data.push_back(instance);       //put finished instance into vector of data
        }
    }

    return Data;
}



int main(int argc, char *argv[]){
    //First read in data, this is your training set
    //using leave one out validator, nearest neighbor classifier, and forward search algorithm, find the highest accuracy of feature combinations
    //return the best features.
    //cout << "The purpose of this program is to take in a file of classified data points as input and output the best combination of features" << endl;

    string filename;
    if(argc == 2){
        filename = argv[1];
    }
    else{
        if(argc < 2){
            cout << "ERROR: Not enough arguments, include a file of data points" << endl;
        }
        else if(argc > 2){
            cout << "ERROR: Too many arguments, only include one file of data points" << endl;
        }
    }
    vector<point> Data = import_data(filename);     //read in data points and store in a vector
    vector<int> best_features = forwardSearchAlgorithm(Data);

    cout << "The best features are: ";
    for(int i = 0; i < best_features.size(); i++){
        cout << best_features.at(i) << " " ;
    }
    cout << endl;


    return 0;
}