#include <iostream>

#include <vector>
#include <string>
#include <math.h>
using namespace std;

void readCsv(string filename, vector<vector<float>>& ans);

double getEntropy(vector<float>& quality_score){
    int data_points = quality_score.size();
    auto it_max = max_element(std::begin(quality_score), std::end(quality_score));
    //   auto it_min = min_element(std::begin(quality_score), std::end(quality_score));
    int max_q = *it_max;
    vector<float> count(max_q+1, 0);
    for(int i = 0; i < data_points; i++)
        count[quality_score[i]]++;
    double entropy = 0;
    for(int i=0; i<count.size(); i++){
        float proportion = count[i]/data_points;
        if(proportion!=0)
            entropy += (-1)*proportion*log2(proportion);
    }

    return entropy;
}

float getThresholdSplit(vector<vector<float>> &data_mat, int attribute){
    vector<float> attribute_column;
    for(int i=0; i<data_mat.size(); i++)
        attribute_column.push_back(data_mat[i][attribute]);
     sort(attribute_column.begin(), attribute_column.end());
    int midway = attribute_column.size()/2;
    return attribute_column[midway];
}

vector<float> getQualityScore(vector<vector<float>> &data_mat){
    vector<float> quality_score;
    for(int i = 0; i<data_mat.size(); i++)
        quality_score.push_back(data_mat[i][data_mat.at(0).size()-1]);

//    for (int i=0; i<quality_score.size(); i++){
//        if(isnan(quality_score[i]))
//            cout << quality_score[i];
//    }
    return quality_score;

}

float computeInfoGain(vector<vector<float>> &data_mat, int attribute){
    float threshold = getThresholdSplit(data_mat, attribute);
    vector<vector<float> > left_child;
    vector<vector<float> > right_child;
    for(int i=0; i<data_mat.size(); i++){
        if(data_mat[i][attribute] <= threshold)
            left_child.push_back(data_mat[i]);
        else
            right_child.push_back(data_mat[i]);
    }
    vector<float> qScore_p = getQualityScore(data_mat);
    vector<float> qScore_l = getQualityScore(left_child);
    vector<float> qScore_r = getQualityScore(right_child);
    float entropy_left = getEntropy(qScore_l);
    float entropy_right = getEntropy(qScore_r);
    float entropy_parent = getEntropy(qScore_p);
    float no_left = left_child.size();
    float no_right = right_child.size();
    float no_total = data_mat.size();
    float pL = (no_left/no_total);
    float pR = (no_right/no_total);
    float avgEntropy = pL*entropy_left + pR*entropy_right;
    float infoGain = entropy_parent - avgEntropy;
    return infoGain;
}


vector<float> getInfoGainVector(vector<vector<float>> &data_mat){
    int no_of_attributes = data_mat[0].size()-1;
    vector<float> infoGainVec(no_of_attributes, 0);
    for(int i = 0; i< no_of_attributes; i++){
        float infoG = computeInfoGain(data_mat, i);
        infoGainVec.push_back(infoG);
    }
    return infoGainVec;
}



int main() {
    vector<vector<float>> data_mat;
    readCsv("/Users/jatin/CLionProjects/ID3/winequality-red.csv", data_mat);
    vector<float> getInfoGainVec = getInfoGainVector(data_mat);
    int split_attribute = 
    for(int i=0; i<getInfoGainVec.size(); i++)
        cout << getInfoGainVec[i] << " ";

//    for(int i = 0; i<data_mat.size(); i++) {
//        for (int j = 0; j < data_mat.at(0).size(); j++)
//            cout << data_mat[i][j] << " ";
//            cout<<endl;
//    }

    //computeInfoGain(data_mat, 1);


//    float entropy = getEntropy(quality_score);
//    cout << entropy;
    return 0;
}












//for(int i = 0; i<ans.size(); i++) {
//for (int j = 0; j < ans.at(0).size(); j++)
//cout << ans[i][j] << " ";
//cout<<endl;
//}



