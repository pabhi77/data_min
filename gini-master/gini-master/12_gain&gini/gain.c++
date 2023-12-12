#include <bits/stdc++.h>
using namespace std;

// Global variables to store data and results
vector<string> sub_classes;
map<string, int> mainClass;
map<string, unordered_set<string>> dist_val;
map<string, int> dist_val_count;
map<string, map<string, int>> val_count;

// Variable to keep track of maximum gain and selected root
double maxGain = DBL_MIN;
string root = "null";

// Output file stream
ofstream fw("gain_output.csv", ios::out);

// Function to calculate the information gain and select the root
void calculateGain(string subClass, double mainC_gain)
{
    double totR = mainClass["class1"] + mainClass["class2"];
    double ent = 0;

    for (auto dv : dist_val[subClass])
    {
        double tR = dist_val_count[dv];
        double pR = val_count[dv]["class1"], nR = val_count[dv]["class2"];

        if (pR != 0)
            ent += -(tR / totR) * ((pR / tR) * log2(pR / tR));

        if (nR != 0)
            ent += -(tR / totR) * ((nR / tR) * log2(nR / tR));
    }

    // Calculate information gain
    double gain = mainC_gain - ent;

    // Output results
    cout << "Information Gain ( " << subClass << "| c ) : " << gain << "\n";
    fw << "Information Gain ( " << subClass << "| c )," << gain << "\n";

    if (gain > maxGain)
    {
        maxGain = gain;
        root = subClass;
    }
}

int main()
{
    // Open and read the input file
    fstream file("gain_input.csv", ios::in);
    string line, word;
    string x,y,z,c;

    if (!file.is_open())
    {
        cerr << "Error in opening input file." << endl;
        return -1;
    }

    int j = 0;

    while (getline(file, line))
    {
        stringstream str(line);

        // Parse the input data
        getline(str, x, ',');
        getline(str, y, ',');
        getline(str, z, ',');
        getline(str, c, ',');
       

        if (j == 0)
        {
            j++;
            sub_classes.push_back(x);
            sub_classes.push_back(y);
            sub_classes.push_back(z);
            
          
            continue;
        }

        // Store data for calculations
        dist_val["x"].insert(x);
        dist_val["y"].insert(y);
        dist_val["z"].insert(z);
        
       

        mainClass[c]++;

        dist_val_count[x]++;
        dist_val_count[y]++;
        dist_val_count[z]++;
      
       

        val_count[x][c]++;
        val_count[y][c]++;
        val_count[z][c]++;
        
    }

    // Calculate entropy for the main class
    double posR = mainClass["class1"];
    double negR = mainClass["class2"];
    double totR = posR + negR;

    double mainC_gain = -((posR / totR) * log2(posR / totR) + (negR / totR) * log2(negR / totR));

    // Output the main class gain
    cout << "Main Class Information Gain : " << mainC_gain << "\n";

    // Calculate and output information gain for each subclass
    for (int i = 0; i < 3; i++)
    {
        calculateGain(sub_classes[i], mainC_gain);
    }

    // Output the selected root with maximum gain
    cout << "The selected root for splitting is: " << root << " (Maximum Gain)"
         << "\n";
    fw << "The selected root for splitting is: " << root << " (Maximum Gain)"
       << "\n";

    return 0;
}