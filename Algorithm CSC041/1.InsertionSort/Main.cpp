
#include <iostream>
#include "InsertionSort.h"
using namespace std;


int main() {
    vector<int> array = {19, 29, 2, 27, 3, 23, 5, 9, 8, 0};

    cout << "Before sorting: ";
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    
    InsertionSort::sort(array);

    cout << endl << "After sorting: ";
    for (int i = 0; i < array.size(); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    return 0;
}
