#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <chrono> 

using namespace std;

struct point {
    int classification;
    vector<double> features;  

};


int nearestNeighborClassifier(vector<int> Chosen_Feature_indexes, int instance_index, vector<point> test_data, vector<point> normalized_data){
    //first find all points (is there a better way? yes, remove instances that obviously wont be considered by sorting)
    //normalize data for a point is Feature1 = (feature1_value - mean(feature1)) / stddev(feature1)
    //then calculate distances and find nearest neighbor with dist between point1 and point2 = 
    // sqrt( pow(2,point1(feature1) - point2(feature1)) +  pow(2,point1(feature2) - point2(feature2)) + ...)
    //return classification



    double min_distance = 1.79769e+308;
    double temp_min_distance = 0.0;
    int closest_point;
    vector<double> normalized_instance;
    for(int i = 0; i < normalized_data.at(instance_index).features.size(); i++){
        normalized_instance.push_back(normalized_data.at(instance_index).features.at(i));
    }
    normalized_data.erase(normalized_data.begin() + instance_index);

    for(int i = 0; i < test_data.size(); i++){
        for(int k = 0; k < Chosen_Feature_indexes.size(); k++){
            temp_min_distance += pow(normalized_instance.at(Chosen_Feature_indexes.at(k)) - normalized_data.at(i).features.at(Chosen_Feature_indexes.at(k)), 2);
           // cout << "point1 - point2: " << normalized_instance.at(Chosen_Feature_indexes.at(k)) << " - " << normalized_data.at(i).features.at(Chosen_Feature_indexes.at(k)) << endl;
        }
       // cout << "temp_min_distance = " << temp_min_distance << endl;
        temp_min_distance = sqrt(temp_min_distance);
        //cout << "temp_min_distance after sqrt= " << temp_min_distance << endl;
        if(temp_min_distance < min_distance){
            min_distance = temp_min_distance;
            closest_point = i;
        }
        temp_min_distance = 0.0;
    }

   // cout << "closest point = " << closest_point << endl;
    
   // exit(1);
    return test_data.at(closest_point).classification;
}



//Create Leave one out validator (need training data and the classifier) 
float leaveOneOutValidator(vector<point> Data, vector<int> current_features, int feature_to_add, vector<point> normalized_data){
    double accuracy = 0.0;
    vector<int> all_features = current_features;

    //for forwards search algorithm to work
    if(find(all_features.begin(), all_features.end(), feature_to_add) == all_features.end()){   //if the feature to add is not already in all features
        all_features.push_back(feature_to_add);
    }
    //for backwards search to work
    else{                                                                                       //if feature to add is already in all features
        all_features.erase(remove(all_features.begin(), all_features.end(), feature_to_add), all_features.end());
    }
    int num_points = Data.size();
    vector<point> test_data = Data;
    int correct_classification;
    int guessed_classification;
    int correct_class_count = 0;
    
      
    for(int i = 0; i < num_points; i++){
       test_data.erase(test_data.begin() + i);  //erase the leave one out point
       correct_classification = Data.at(i).classification;
       guessed_classification = nearestNeighborClassifier(all_features, i, test_data, normalized_data);
       //cout << "guess classification = " << guessed_classification << endl;
       if(correct_classification == guessed_classification){
           correct_class_count++;
       }
       test_data = Data;
    }

    accuracy = static_cast<double>(correct_class_count) / static_cast<double>(num_points);

   // cout << "accuracy: " << accuracy << endl;

    return accuracy;
}


//Create forward and backwards search algorithm (adds or removes features and assigns accuracy score to the combinations and chooses highest one)
vector<int> forwardSearchAlgorithm(vector<point> Data){
    double accuracy = 0.0;
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

    //normalized the data for nearest neighbor
    double normalized_feature;
    vector<point> normalized_data;
    

    for(int i = 0; i < Data.size(); i++){
        point normalized_point;
        //cout << "normalized features: " ;
        for(int k = 0; k < Data.at(0).features.size(); k++){
            normalized_feature = (Data.at(i).features.at(k) - min_vect.at(k)) / (max_vect.at(k) - min_vect.at(k));
            normalized_point.features.push_back(normalized_feature);
            //cout << normalized_feature << " ";
        }
        //cout << endl;
        normalized_data.push_back(normalized_point);
    }

    
    double best_accuracy_so_far = 0.0;

    //forward search algorithm
    for(int i = 0; i < Data.at(0).features.size(); i++){
        int feature_to_add = -1;
        
    
        for(int k = 0; k < (Data.at(0).features.size() - current_set_of_features.size()); k++){
            if(find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end()){  //if k is not in current features
                accuracy = leaveOneOutValidator(Data, current_set_of_features, k, normalized_data);
                if(accuracy >= best_accuracy_so_far){
                    best_accuracy_so_far = accuracy;
                    feature_to_add = k;
                }
            }   
        }
        if(feature_to_add == -1){
            break;
        }
        cout << "adding feature to set, feature is: " << feature_to_add + 1 << " accuracy is " << best_accuracy_so_far * 100.00 << "%" << endl;
        current_set_of_features.push_back(feature_to_add);
    }

    cout << "best accuracy is: " << best_accuracy_so_far * 100.00 << "%" << endl;

    return current_set_of_features;
}


vector<int> backwardSearchAlgorithm(vector<point> Data){
    double accuracy = 0.0;
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

    //normalized the data for nearest neighbor
    double normalized_feature;
    vector<point> normalized_data;
    

    for(int i = 0; i < Data.size(); i++){
        point normalized_point;
        //cout << "normalized features: " ;
        for(int k = 0; k < Data.at(0).features.size(); k++){
            normalized_feature = (Data.at(i).features.at(k) - min_vect.at(k)) / (max_vect.at(k) - min_vect.at(k));
            normalized_point.features.push_back(normalized_feature);
            //cout << normalized_feature << " ";
        }
        //cout << endl;
        normalized_data.push_back(normalized_point);
    }

    

    //backward search algorithm
    double best_accuracy_so_far = 0.0;
    for(int i = 0; i < Data.at(0).features.size(); i++){    //fill set with all features
        current_set_of_features.push_back(i);
    }

    for(int i = Data.at(0).features.size()-1; i >= 0; i--){
        int feature_to_subtract = -1;
     
    
        for(int k = Data.at(0).features.size()-1; k >= 0; k--){
            if(find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()){  //if k is in current features
                accuracy = leaveOneOutValidator(Data, current_set_of_features, k, normalized_data);
                if(accuracy >= best_accuracy_so_far){
                    best_accuracy_so_far = accuracy;
                    feature_to_subtract = k;
                }
            }   
        }
        if(feature_to_subtract == -1){
            break;
        }
        cout << "removing feature from set, feature is: " << feature_to_subtract + 1 << " accuracy is " << best_accuracy_so_far * 100.00 << "%" << endl;
        current_set_of_features.erase(remove(current_set_of_features.begin(), current_set_of_features.end(), feature_to_subtract), current_set_of_features.end());
    }

    cout << "best accuracy is: " << best_accuracy_so_far * 100.00 << "%" << endl;
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
    int algorithm_choice;
    vector<int> best_features;
    vector<point> Data = import_data(filename);     //read in data points and store in a vector
    cout << "Enter 1 for forward search algorithm and 2 for backwards search algorithm" << endl;
    cin >> algorithm_choice;
    if(algorithm_choice == 1){
        //start timer
        chrono::time_point<chrono::system_clock> start, end; 
        start = chrono::system_clock::now(); 

        best_features = forwardSearchAlgorithm(Data);

        //end timer
        end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start; 
        cout << "total time: " << elapsed_seconds.count() << " seconds" << endl; 
    }
    else if(algorithm_choice == 2){
        //start timer
        chrono::time_point<chrono::system_clock> start, end; 
        start = chrono::system_clock::now(); 

        best_features = backwardSearchAlgorithm(Data);

        end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start; 
        cout << "total time: " << elapsed_seconds.count() << " seconds" << endl; 
    }
    else{
        cout << "not a valid choice" << endl;
        return 0;
    }
    
     

    cout << "The best features are: ";
    for(int i = 0; i < best_features.size(); i++){
        cout << best_features.at(i) + 1 << " " ;
    }
    cout << endl;


    return 0;
}