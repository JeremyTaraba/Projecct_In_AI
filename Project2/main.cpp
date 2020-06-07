#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

//just for testing
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

struct point {
    int classification;
    vector<double> features;  

};

//gives us two vectors, one with mean values for each feature and one with stddev for each feature
vector< vector<double> > mean_and_standardDev(vector<point> Data){
    //finds the sum
    vector< vector<double> > mean_stddev;
    vector<double> sum_vect;
    double sum = 0;
    for(int i = 0; i < Data.at(0).features.size(); i++){
        for(int k = 0; k < Data.size(); k++){
            sum += Data.at(k).features.at(i);
        }
        sum_vect.push_back(sum);
        sum = 0;
    }
    //finds the mean
    vector<double> mean;
    for(int i = 0; i < Data.at(0).features.size(); i++){
        mean.push_back( sum_vect.at(i) / Data.size() );
    }
    mean_stddev.push_back(mean);

    //find the standard deviation
    double stddev;
    vector<double> stddev_vect;
    for(int i = 0; i < Data.at(0).features.size(); i++){
        for(int k = 0; k < Data.size(); k++){
            stddev += pow(Data.at(k).features.at(i) - mean.at(i), 2);
        }
        stddev_vect.push_back(sqrt( stddev / Data.size()));
        cout << "for feature " << i << " stddev = " << stddev_vect.at(i) << "    mean = " << mean.at(i) << endl;
        stddev = 0;
    }
    mean_stddev.push_back(stddev_vect);

    return mean_stddev;
}

int nearestNeighborClassifier(vector<int> Chosen_Feature_indexes, point instance, vector<point> test_data, vector<double> mean, vector<double> stddev){
    //first find all points (is there a better way? yes, remove instances that obviously wont be considered by sorting)
    //normalize data for a point is Feature1 = (feature1_value - mean(feature1)) / stddev(feature1)
    //then calculate distances and find nearest neighbor with dist between point1 and point2 = sqrt( pow(2,point1(feature1) - point2(feature1)) )
    //return classification

    int closest_point = 0;      //set closest point to a random point in the test_data
    vector< vector<double> > normalized_features_test;
    vector<double> normalized_features_instance;
    //we need to store x,y and z features in the normalized feature set (columns) go over 1 feature for all points not all features for one point
    double normalized_feature;

    //create all normalized features for the instance
    for(int i = 0; i < instance.features.size(); i++){
        normalized_feature = (instance.features.at(i) - mean.at(i)) / stddev.at(i);
        normalized_features_instance.push_back(normalized_feature);
    }

    //create all normalized features for the test set
    for(int i = 0; i < test_data.at(0).features.size(); i++){
        for(int k = 0; k < test_data.size(), k++){
            normalized_feature = (test_data.at(k).features.at(i) - mean.at(i)) / stddev.at(i);
            normalized_features_test.at(k).push_back(normalized_feature);
        }
    }

    

    return rand() % 2 + 1;
}




//Create Leave one out validator (need training data and the classifier) 
float leaveOneOutValidator(vector<point> Data, vector<int> current_features, int feature_to_add, vector<double> mean, vector<double> stddev){
    double accuracy = 0.0;
    vector<int> all_features = current_features;
    all_features.push_back(feature_to_add);
    int num_points = Data.size();
    vector<point> test_data = Data;
    int correct_classification;
    int guessed_classification;
    int correct_class_count = 0;
    
    for(int i = 0; i < num_points; i++){
       test_data.erase(test_data.begin() + i);  //erase the leave one out point
       correct_classification = Data.at(i).classification;
       guessed_classification = nearestNeighborClassifier(all_features, Data.at(i), test_data, mean, stddev);
       if(correct_classification == guessed_classification){
           correct_class_count++;
       }
       test_data = Data;
    }

    accuracy = static_cast<double>(correct_class_count) / static_cast<double>(num_points);

    cout << "accuracy: " << accuracy << endl;

    return accuracy;
}


//Create Forward search algorithm (adds or removes features and assigns accuracy score to the combinations and chooses highest one)
vector<int> forwardSearchAlgorithm(vector<point> Data){
    double accuracy = 0;
    vector<int> current_set_of_features;

    //find mean and stddev for normalization
    vector< vector<double> > mean_stddev = mean_and_standardDev(Data);
    vector<double> mean = mean_stddev.at(0);
    vector<double> stddev = mean_stddev.at(1);
    

    for(int i = 0; i < Data.at(0).features.size(); i++){
        int feature_to_add;
        double best_accuracy_so_far = 0.0;
        
        for(int k = 0; k < Data.at(0).features.size(); k++){
            if(find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()){  //if k is not in current features
                accuracy = leaveOneOutValidator(Data, current_set_of_features, k, mean, stddev);
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