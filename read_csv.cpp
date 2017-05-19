#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
enum DataType {INT, FLOAT, STRING};

struct SchemaTuple {
    string name;
    DataType type;
    bool isResult;
    SchemaTuple(string name, DataType type, bool isResult) : name(name), type(type), isResult(isResult) {};
};


void readCsv(string filename, vector<vector<string>>& ans);
void splitString(vector<string> &line, string str);


void readCsv(string filename, vector<vector<string>>& ans) {
    ifstream file(filename);
    string value;
    while ( file.good() )
    {
        getline(file, value);
        vector<string> parts;
        splitString(parts, value);
        ans.push_back(parts);
    }
    file.close();
}

void splitString(vector<string> &line, string str) {
    int start = 0;
    for(int i = 0; i<str.length(); i++) {
        if(str.at(i)==';'){
            line.push_back(str.substr(start, i-start));
            start = i+1;
        }
    }
    line.push_back(str.substr(start,str.length()-start));
}

void createSchema(vector<SchemaTuple*>& schema) {
    schema.push_back(new SchemaTuple("sepal_l", FLOAT, false));
    schema.push_back(new SchemaTuple("sepal_w", FLOAT, false));
    schema.push_back(new SchemaTuple("petal_l", FLOAT, false));
    schema.push_back(new SchemaTuple("petal_w", FLOAT, false));
    schema.push_back(new SchemaTuple("class", STRING, true));
}
