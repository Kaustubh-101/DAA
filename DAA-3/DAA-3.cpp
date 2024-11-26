#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 
using namespace std; 
 
int findMax(vector<double> a, int lo, int hi) 
{ 
 
    if (lo > hi) 
        return -1; 
  
    if (lo == hi) 
        return a[lo]; 
    int mid = (lo + hi) / 2; 
    int leftMax = findMax(a, lo, mid); 
    int rightMax = findMax(a, mid + 1, hi); 
    return max(leftMax, rightMax); 
} 
int findMin(vector<double> a, int lo, int hi) 
{ 
    if (lo > hi) 
        return -1 ; 
  
    if (lo == hi) 
        return a[lo]; 
    int mid = (lo + hi) / 2; 
    int leftMin = findMin(a, lo, mid); 
    int rightMin = findMin(a, mid + 1, hi); 
    return min(leftMin, rightMin); 
} 
 
 
int main() 
{ 
    ifstream inputFile("1input.csv"); // Input CSV file 
    ofstream outputFile("1.csv");  // Output CSV file 
    vector<double>v; 
        if (!inputFile.is_open() || !outputFile.is_open()) 
    { 
        cout << "Error opening file!" << endl; 
 
    } 
 
    string line; 
    // Write the header for the output file 
    outputFile << "Name,Salary,Tax,Home Rent,Bonus\n"; 
 
    // Skip the header line in the input file 
    getline(inputFile, line); 
 
    // Process each line 
    while (getline(inputFile, line)) 
    { 
        stringstream ss(line); 
        string name, salaryStr; 
        getline(ss, name, ','); 
        getline(ss, salaryStr, ','); 
 
        double salary = stod(salaryStr); 
        v.push_back(salary); 
        double tax = 0.10 * salary; 
        double homeRent = 0.20 * salary; 
        double bonus = 0.15 * salary; 
 
        // Write the results to the output file 
        outputFile << name << "," << salary << "," << tax << "," << homeRent << "," << bonus << 
"\n"; 
    } 
 
    inputFile.close(); 
    outputFile.close(); 
 
    cout << "Calculations completed and output saved to 'output_finances.csv'." << endl; 
 
    if(findMin(v,0,2000)<0){ 
        cout<<"Salary can't be negative"; 
    } 
    else{ 
    cout<<"Min Salary -> "<<findMin(v,1,2000)<<endl; 
    cout<<"Max Salary -> "<<findMax(v,1,2000); 
    } 
 
    return 0; 
} 
