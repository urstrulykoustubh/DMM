#include<bits/stdc++.h>
using namespace std;

int main(){

    fstream file("input.csv",ios::in);

    if(!file.is_open()){
        cout << "Error in opening file";
        return 0;
    }

    string line,mark;
    vector<double> marks;

    int i=0;
    while(getline(file,line)){

        if(i==0){
            i++;
            continue;
        }

        stringstream str(line);
        getline(str,mark,',');
        double mk = stod(mark);
        marks.push_back(mk);

    }

    int n = marks.size();

    sort(marks.begin(),marks.end());

    file.close();

    double sum = 0;
    for(auto mk : marks){
        sum += mk;
    }

    double mean = sum/n;

    double dev_sq = 0;
    for(auto mk : marks){
        dev_sq += (mk - mean)*(mk - mean);
    }

    double std_dev = sqrt(dev_sq/n);

    ofstream fw2("zscore_normalized_data1.csv",ios::out);

    if(!fw2.is_open()){
        cout << "Error in creating Z-score Normalized data file.";
        return -1;
    }

    fw2 << "Marks " << "," << "Z-Score Normalized Marks " << endl;

    for(auto mk : marks){
        double z_score = (mk - mean)/std_dev;

        fw2 << mk << "," << z_score << endl;
    }

    fw2.close();
    return 0;
}