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

    double old_min=marks[0],old_max=marks[n-1];
    double new_min,new_max;

    cout << "Enter New Minimum : ";
    cin >> new_min;

    cout << "Enter New Maximum : ";
    cin >> new_max;

    ofstream fout("min_max_normalized_data1.csv",ios::out);

    if(!fout.is_open()){
        cout << "Error in creating min-max-normalization file";
        return -1;
    }

    fout << "Marks" << "," << "Min-max_normalized Marks" << endl;

    for(auto x : marks){
        double normalized_marks = (((x-old_min)/(old_max-old_min))*(new_max - new_min)) + new_min;

        fout << x << "," << normalized_marks << endl;
    }
    fout.close();
    file.close();

    return 1;
}