#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<bits/stdc++.h>
 
using namespace std;
 
int main()
{
    fstream file ("data.csv", ios::in);

    if(!file.is_open()){
        cout << "COuldn't Open file";
        return 0;
    }

    string line, word;
    string cat,region,count;
    int val ;
    
    map<string,map<string,int>> classRegionMap;
    map<string,int> catMap;
    map<string,int> regMap;

    int i=0;

    while(getline(file, line))
    {
        stringstream str(line);

        if(i==0){
            i++;
            continue;
        }
            
        getline(str, cat, ',');
        getline(str, region, ',');
        getline(str, count, ',');

        val = stoi(count);

        // cout << cat << " " << region << " "<< stoi(count)+10 << " " << "\n";

        classRegionMap[cat][region] = val;
        catMap[cat] += val;
        regMap[region] += val;

    }

    for(auto p : classRegionMap){
        for(auto pp : p.second){

            cat = p.first;
            region = pp.first;
            val = pp.second;

            double tweight = 0,dweight=0;

            tweight = ((double)(classRegionMap[cat][region]) / catMap[cat])*100;
            dweight = ((double)(classRegionMap[cat][region]) / regMap[region])*100;

            cout << "T-weight for [" << cat << "][" << region << "] : " << tweight << "%" << "\n";
            cout << "D-weight for [" << cat << "][" << region << "] : " << dweight << "%" <<"\n\n";
        }
    }

    int catSum = 0,regSum=0;

    for(auto p : catMap){
        catSum += p.second;
    }     

    // cout << "catSum : " << catSum << "\n";  

    for(auto p : regMap){
        regSum += p.second;
    }

    // cout << "regSum : " << regSum << "\n\n";

    for(auto p : regMap){
        region = p.first;
        double tweight = 0,dweight=0;

        tweight = ((double)(regMap[region]) / catSum)*100;
        dweight = ((double)(regMap[region]) / regMap[region])*100;

        cout << "T-weight for [Both Classes][" << region << "] : " << tweight << "%" << "\n";
        cout << "D-weight for [Both Classes][" << region << "] : " << dweight << "%" <<"\n\n";

    } 

    for(auto p : catMap){
        cat = p.first;
        double tweight = 0,dweight=0;

        tweight = ((double)(catMap[cat]) / catMap[cat])*100;
        dweight = ((double)(catMap[cat]) / regSum)*100;

        cout << "T-weight for [" << cat << "][Both Regions] : " << tweight << "%" << "\n";
        cout << "D-weight for [" << cat << "][Both Regions] : " << dweight << "%" <<"\n\n";

    }
 
    return 0;
}
 
 
