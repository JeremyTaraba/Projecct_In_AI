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
        stddev = 0;
    }
    mean_stddev.push_back(stddev_vect);

    return mean_stddev;
}

int nearestNeighborClassifier(vector<int> Chosen_Feature_indexes, point instance, vector<point> test_data, vector<double> min_vect, vector<double> max_vect){
    //first find all points (is there a better way? yes, remove instances that obviously wont be considered by sorting)
    //normalize data for a point is Feature1 = (feature1_value - mean(feature1)) / stddev(feature1)
    //then calculate distances and find nearest neighbor with dist between point1 and point2 = 
    // sqrt( pow(2,point1(feature1) - point2(feature1)) +  pow(2,point1(feature2) - point2(feature2)) + ...)
    //return classification
    
    vector<double> normalized_instance;
    double normalized_feature;
    int closest_point;
    vector<point> normalized_data;
    point normalized_point;
    double min_distance = 1.79769e+308;
    double temp_min_distance = 0.0;

    for(int i = 0; i < instance.features.size(); i++){
        normalized_feature = (instance.features.at(i) - min_vect.at(i)) / (max_vect.at(i) - min_vect.at(i));
        normalized_instance.push_back(normalized_feature);
        //cout << "normalized instance value for feature " << i+1 << " is "<< normalized_feature << endl;
    }

    for(int i = 0; i < test_data.size(); i++){
        for(int k = 0; k < test_data.at(0).features.size(); k++){
            normalized_feature = (test_data.at(i).features.at(k) - min_vect.at(k)) / (max_vect.at(k) - min_vect.at(k));
            normalized_point.features.push_back(normalized_feature);
        }
        normalized_data.push_back(normalized_point);
    }
    //output data points in 2d space


    for(int i = 0; i < test_data.size(); i++){
        for(int k = 0; k < Chosen_Feature_indexes.size(); k++){
            temp_min_distance += pow(2, normalized_instance.at(Chosen_Feature_indexes.at(k)) - normalized_data.at(i).features.at(Chosen_Feature_indexes.at(k)));
        }
        temp_min_distance = sqrt(temp_min_distance);
        cout << "temp_min_distance = " << temp_min_distance << endl;
        if(temp_min_distance < min_distance){
            min_distance = temp_min_distance;
            closest_point = i;
        }
        temp_min_distance = 0.0;
    }

    cout << "closest point = " << closest_point << endl;


    // vector<point> data;
    // point normalized_instance;
    // double distance_between = 0;
    // int closest_point;
    // double min_Dist = 2147483647;

    
    // normalized_features_instance.push_back( (instance.features.at(0) - min) / (max - min)); 
    // cout << "normalized instance = " << normalized_features_instance.at(0) << endl;
    

    // for(int i = 0; i < test_data.size(); i++){
    //     normalized_instance.features.push_back( static_cast<double>( ( static_cast<double>(test_data.at(i).features.at(0)) - static_cast<double>(min) ) / static_cast<double>(max - min)) ); 
    //     cout << "test features at 0 = " << test_data.at(i).features.at(0);
    //     data.push_back(normalized_instance);
    //     cout << " normalized test = " << data.at(i).features.at(0) << endl;
    // }
    

    // for(int i = 0; i < test_data.size(); i++){
    //     for(int k = 0; k < normalized_features_instance.size(); k++){
    //         distance_between += pow(2, normalized_features_instance.at(k) - data.at(i).features.at(k) );
    //     }
    //     distance_between = sqrt(distance_between);
    //     cout << "data.at(i).features.at(k) = " << data.at(i).features.at(0) << endl;
    //     if(distance_between < min_Dist){
    //         min_Dist = distance_between;
    //         closest_point = i;
    //         cout << "set closest point as " << i << " distance of " << min_Dist << endl;
    //     }
    // }
    
    exit(1);
    return test_data.at(closest_point).classification;
}




//Create Leave one out validator (need training data and the classifier) 
float leaveOneOutValidator(vector<point> Data, vector<int> current_features, int feature_to_add, vector<double> min, vector<double> max){
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
       guessed_classification = nearestNeighborClassifier(all_features, Data.at(i), test_data, min, max);
       //cout << "guess classification = " << guessed_classification << endl;
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

    //find min and max for each feature for normalization
    vector<double> min_vect;
    vector<double> max_vect;
    double min_feature = 1.79769e+308;
    double max_feature = 2.22507e-308;

    for(int i = 0; i < Data.at(0).features.size(); i++){
        for(int k = 0; k < Data.size(); k++){
            if(Data.at(k).features.at(i) > max_feature){
                max_feature = Data.at(k).features.at(i); 
            }
            if(Data.at(k).features.at(i) < min_feature){
                min_feature = Data.at(k).features.at(i); 
            }
        }
        min_vect.push_back(min_feature);
        max_vect.push_back(max_feature);
        min_feature = 1.79769e+308;
        max_feature = 2.22507e-308;
    }   

    for(int k = 0; k < Data.at(0).features.size(); k++){
        cout << "for feature " << k + 1 << " min = " << min_vect.at(k) << " max = " << max_vect.at(k) << endl;
    }



    for(int i = 0; i < Data.at(0).features.size(); i++){
        int feature_to_add;
        double best_accuracy_so_far = 0.0;
        
        for(int k = 0; k < Data.at(0).features.size(); k++){
            if(find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()){  //if k is not in current features
                accuracy = leaveOneOutValidator(Data, current_set_of_features, k, min_vect, max_vect);
                if(accuracy > best_accuracy_so_far){
                    best_accuracy_so_far = accuracy;
                    feature_to_add = k;
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
        cout << best_features.at(i) + 1 << " " ;
    }
    cout << endl;


    return 0;
}