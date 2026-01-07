#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <ctime>   

using namespace std;


void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { 
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid); 
    mergeSort(arr, mid + 1, right); 
    merge(arr, left, mid, right);
}

int main() {
    
    const int NUM_ELEMENTS = 10;
    vector<int> arr(NUM_ELEMENTS);
    
  
    srand(time(0)); 

    cout << "Bilangan acak yang dihasilkan (" << NUM_ELEMENTS << " elemen antara 1-100):" << endl;
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        
        arr[i] = (rand() % 100) + 1; 
    }

    
    cout << "Sebelum diurutkan: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    
    mergeSort(arr, 0, NUM_ELEMENTS - 1);

    
    cout << "Setelah diurutkan (Ascending): ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}