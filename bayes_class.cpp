#include <bits/stdc++.h>
using namespace std;

int main()
{
    string line, word;
    ifstream file("input1.csv");

    string day;
    map<string, double> parent;
    map<string, map<string, map<string, double>>> child;
    int count = 0;

    vector<string> title;
    if (file.is_open())
    {
        int i = 0;
 
        while (file >> line)
        {
            stringstream str(line);
            if (i == 0)
            {
                string heading;
                while (getline(str, heading, ','))
                {
                    title.push_back(heading);
                }
                i++;
                continue;
            }

            vector<string> columns;
            while (getline(str, day, ','))
            {
                columns.push_back(day);
            }
 
            int n = columns.size();
 
            parent[columns[n - 1]]++;
            for (int i = 1; i < n - 1; i++)
            {
                child[title[i]][columns[i]][columns[n - 1]]++;
            }
 
            count++;
        }
 
        vector<string> resultclass;
        for (auto it : parent)
        {
            resultclass.push_back(it.first);
        }
 
        vector<double> output(resultclass.size(), 1);

        for (auto it : child)
        {
            string input;
        again:
            cout << "\nEnter " << it.first << " condition : ";
            cin >> input;
 
            auto curr = child[it.first].find(input);
            if (curr == child[it.first].end())
            {
                cout << "no match\n";
                goto again;
            }

            for (int i = 0; i < resultclass.size(); i++)
            {
 
                cout << "P(" << it.first << "=" << input << "& playGame=" << resultclass[i] << ") = " << child[it.first][input][resultclass[i]] << " / " << parent[resultclass[i]] << endl;
                double val = child[it.first][input][resultclass[i]] / parent[resultclass[i]];
                output[i] *= val;

                cout << output[i] << "\n";
            }
        }
 
        for (int i = 0; i < resultclass.size(); i++)
        {
            output[i] *= parent[resultclass[i]] / count;
        }

        string opclass = "null";
        double maxprob = -1;

        ofstream fw("output1.csv",ios::out);

        for (int i = 0; i < resultclass.size(); i++)
        {
            cout << "Px(" << resultclass[i] << ") = " << " " << output[i] << endl;
            fw << "Px(" << resultclass[i] << ") : " << "," << output[i] << "\n";
            
            if(output[i] > maxprob){
                maxprob = output[i];
                opclass = resultclass[i];
            }
        }

        cout << "Therefore the given condition belong to class : " << opclass << "\n";
        fw << "\n";
        fw << "Therefore the given condition belong to class : " << opclass << "\n";
    }
    else
    {
        cout << "Could not open the file\n";
    }
 
    return 0;
}