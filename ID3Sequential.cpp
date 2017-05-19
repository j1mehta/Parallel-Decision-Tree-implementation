#include <iostream>

#include <vector>
#include <string>
#include <math.h>
using namespace std;

void readCsv(string filename, vector<vector<string>>& ans);

double getEntropy(vector<int>& quality_score){
    int data_points = quality_score.size();
    auto it_max = max_element(std::begin(quality_score), std::end(quality_score));
    //   auto it_min = min_element(std::begin(quality_score), std::end(quality_score));
    int max_q = *it_max;
    vector<int> count(max_q+1, 0);
    for(int i = 0; i < data_points; i++)
        count[quality_score[i]]++;
    double entropy = 0;
    for(int i=0; i<count.size(); i++){
        int proportion = count[i];
        entropy += (-1)*proportion*log2(proportion);
    }

    return entropy;
}

float getThresholdSPlit(vector<vector<string>> &data_mat, int attribute){

}

vector<int> getQualityScore(vector<vector<string>> &data_mat){
    vector<int> quality_score;
    for(int i = 1; i<data_mat.size(); i++)
        try {quality_score.push_back(stoi(data_mat[i][data_mat.at(0).size()-1]));}
        catch (int i){cerr << "String" << data_mat[i][data_mat.at(0).size()-1] << "wasn't converted";}
    return quality_score;
}

float computeInfoGain(vector<vector<string>> &data_mat, int attribute){
    float threshold = getThresholdSPlit(data_mat, attribute);
    vector<vector<string> > left_child;
    vector<vector<string> > right_child;
    for(int i=0; i<data_mat.size(); i++){
        if(data_mat[i][attribute] <= threshold)
            left_child.push_back(data_mat[i]);
        else
            right_child.push_back(data_mat[i]);
    }
    vector<int> qScore_p = getQualityScore(data_mat);
    vector<int> qScore_l = getQualityScore(left_child);
    vector<int> qScore_r = getQualityScore(right_child);
    float entropyParent = getEntropy(qScore_p);
    float entropy_left = getEntropy(qScore_l);
    float entropy_right = getEntropy(qScore_r);
    float entropy_parent = getEntropy(qScore_p);
    int no_left = left_child.size();
    int no_right = right_child.size();
    int no_total = data_mat.size();
    float avgEntropy = (no_left/no_total)*entropy_left + (no_right/no_total)*entropy_right;
    float infoGain = entropy_parent - avgEntropy;
    return infoGain;
}


vector<float> getInfoGainVector(vector<vector<string>> &data_mat){
    int no_of_attributes = data_mat[0].size();
    vector<float> infoGainVec(no_of_attributes, 0);
    for(int i = 0; i< no_of_attributes; i++){
        float infoG = computeInfoGain(data_mat, i);
        infoGainVec.push_back(infoG);
    }
    return infoGainVec;
}

int main() {
    vector<vector<string>> data_mat;
    readCsv("/Users/jatin/CLionProjects/ID3/winequality-red.csv", data_mat);
    return 0;
}
