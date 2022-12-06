#include<bits/stdc++.h>
using namespace std;

vector<string> sub_classes;
map<string,int> mainClass;
map<string,unordered_set<string>> dist_val;
map<string,int> dist_val_count;
map<string,map<string,int>> val_count;

double maxGain = DBL_MIN;
string root = "null";

ofstream fw("output.csv",ios::out);

void calculateGain(string subClass,double mainC_gain){

    double totR = mainClass["Yes"] + mainClass["No"];

    double ent = 0;

    for(auto dv : dist_val[subClass]){
        double tR = dist_val_count[dv];
        double pR = val_count[dv]["Yes"],nR = val_count[dv]["No"];

        if(pR != 0)
            ent += - (tR/totR) * ((pR / tR) * log2(pR / tR));
        
        if(nR != 0)
            ent += - (tR/totR) * ((nR / tR) * log2(nR / tR));
    }

    // cout << "InfoGain ( " << subClass << "|" << "playGame ) : " << ent << "\n";
    // fw << "InfoGain ( " << subClass << "|" << "playGame )," << ent << "\n";

    double gain = mainC_gain - ent;

    cout << "Gain ( " << subClass << "|" << "playGame ) : " << gain << "\n\n";
    fw << "Gain ( " << subClass << "|" << "playGame )," << gain << "\n";

    if(gain > maxGain){
        maxGain = gain;
        root = subClass;
    }

}

int main(){

    fstream file("input.csv", ios::in);

    string line, word;
    string day, outlook, temp, humidity, wind, playGame;

    if (!file.is_open())
    {
        perror("Error in opening input file : ");
        return -1;
    }

    int j = 0;
    string main_class = "playgame";
    
    while (getline(file, line))
    {
        stringstream str(line);

        getline(str, day, ',');
        getline(str, outlook, ',');
        getline(str, temp, ',');
        getline(str, humidity, ',');
        getline(str, wind, ',');
        getline(str, playGame, ',');

        if(j==0){
            j++;
            sub_classes.push_back(day);
            sub_classes.push_back(outlook);
            sub_classes.push_back(temp);
            sub_classes.push_back(humidity);
            sub_classes.push_back(wind);
            continue;
        }

        dist_val["day"].insert(day);
        dist_val["outlook"].insert(outlook);
        dist_val["temp"].insert(temp);
        dist_val["humidity"].insert(humidity);
        dist_val["wind"].insert(wind);

        mainClass[playGame]++;

        dist_val_count[day]++;
        dist_val_count[outlook]++;
        dist_val_count[temp]++;
        dist_val_count[humidity]++;
        dist_val_count[wind]++;

        val_count[day][playGame]++;
        val_count[outlook][playGame]++;
        val_count[temp][playGame]++;
        val_count[humidity][playGame]++;
        val_count[wind][playGame]++;
    }

    double posR = mainClass["Yes"],negR = mainClass["No"];
    double totR = posR + negR;

    double mainC_gain = -((posR / totR) * log2(posR / totR) + (negR / totR) * log2(negR / totR));

    cout << "Main Class Gain : " << mainC_gain << "\n";

    for(int i=1;i<5;i++){
        calculateGain(sub_classes[i],mainC_gain);
    }

    cout << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";
    fw << "Subclass : " << root << " has maximum gain . Hence it will be selected as root for splitting.\n";

    return 0;
}