#include <iostream>
#include <vector>
using namespace std;

// Function to count inversions using brute force
int countInversions(vector<int>& students) {
    int inversions = 0;

    // Iterate through all pairs of students
    for (int i = 0; i < students.size(); ++i) {
        for (int j = i+1; j < students.size(); ++j) { // Ensure j > i
            // Check if there is an inversion
            if (students[i] > students[j]) {
                inversions++;
            }
        }
    }

    return inversions;
}

int main() {
 
    vector<int> students = {10, 5, 2, 7, 3};

    int totalInversions = countInversions(students);

  
    cout << "Total number of inversions: " << totalInversions << endl;

    return 0;
}
