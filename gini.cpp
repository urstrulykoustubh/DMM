#include<bits/stdc++.h>
using namespace std;

vector<string> sub_classes;
map<string,int> mainClass;
map<string,unordered_set<string>> dist_val;
map<string,int> dist_val_count;
map<string,map<string,int>> val_count;

double minGini = DBL_MAX;
string root = "null";

ofstream fw("gini_output.csv",ios::out);

void calculateGini(string subClass,double mainC_gini){

    double totR = mainClass["Yes"] + mainClass["No"];

    double ent = 0;

    for(auto dv : dist_val[subClass]){
        double tR = dist_val_count[dv];
        double pR = val_count[dv]["Yes"],nR = val_count[dv]["No"];

        ent += (tR/totR) * (1 - (pR / tR)*(pR / tR) - (nR / tR)*(nR / tR));
        
    }

    double gini = ent;

    cout << "Gini ( " << subClass << "|" << "playGame ) : " << gini << "\n\n";
    fw << "Gini ( " << subClass << "|" << "playGame )," << gini << "\n";

    if(gini < minGini){
        minGini = gini;
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

    double mainC_gini = 1 - ((posR / totR)* (posR / totR) + (negR / totR)*(negR / totR));

    cout << "Main Class Gain : " << mainC_gini << "\n";

    for(int i=1;i<5;i++){
        calculateGini(sub_classes[i],mainC_gini);
    }

    cout << "Subclass : " << root << " has minimum giniIndex . Hence it will be selected as root for splitting.\n";
    fw << "Subclass : " << root << " has maximum giniIndex . Hence it will be selected as root for splitting.\n";

    return 0;
}