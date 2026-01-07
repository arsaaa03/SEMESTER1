#include <iostream>
#include <vector>
#include <algorithm> 


long long bubbleSort(std::vector<int>& arr) {
    long long langkah = 0;
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - 1 - i; j++) {
            langkah++; 
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
    
        if (swapped == false)
            break;
    }
    return langkah;
}


long long insertionSort(std::vector<int>& arr) {
    long long langkah = 0;
    int n = arr.size();

    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

    
        while (j >= 0) {
            langkah++; 
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            } else {
                break; 
            }
        }
        arr[j + 1] = key;
    }
    return langkah;
}




void tampilkanData(const std::vector<int>& arr) {
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

int main() {
    const int UKURAN = 10;
    std::vector<int> dataAwal;
    int input;

    std::cout << "===== Program Pengurutan Data (Bubble & Insertion Sort) =====\n";
    std::cout << "Masukkan " << UKURAN << " angka integer acak:\n";

    
    for (int i = 0; i < UKURAN; ++i) {
        std::cout << "Angka ke-" << (i + 1) << ": ";
        if (!(std::cin >> input)) {
            std::cout << "Input tidak valid. Program dihentikan.\n";
            return 1;
        }
        dataAwal.push_back(input);
    }
    std::cout << "\n--------------------------------------------------------------\n";

    
    std::cout << "Data Sebelum Diurutkan: ";
    tampilkanData(dataAwal);
    std::cout << "\n";

    
    std::vector<int> dataBubble = dataAwal; 
    long long langkahBubble = bubbleSort(dataBubble);
    
    std::cout << "--- HASIL BUBBLE SORT ---\n";
    std::cout << "Hasil Pengurutan (Ascending): ";
    tampilkanData(dataBubble);
    std::cout << "Jumlah Langkah/Perbandingan: " << langkahBubble << "\n";
    std::cout << "\n";

    
    std::vector<int> dataInsertion = dataAwal; 
    long long langkahInsertion = insertionSort(dataInsertion);
    
    std::cout << "--- HASIL INSERTION SORT ---\n";
    std::cout << "Hasil Pengurutan (Ascending): ";
    tampilkanData(dataInsertion);
    std::cout << "Jumlah Langkah/Perbandingan: " << langkahInsertion << "\n";
    std::cout << "\n";


    std::cout << "=================== KESIMPULAN ===================\n";
    std::cout << "Metode Bubble Sort membutuhkan " << langkahBubble << " langkah.\n";
    std::cout << "Metode Insertion Sort membutuhkan " << langkahInsertion << " langkah.\n";
    
    if (langkahBubble < langkahInsertion) {
         std::cout << "Kesimpulan: Bubble Sort lebih efisien untuk data ini (jumlah langkah lebih sedikit).\n";
    } else if (langkahInsertion < langkahBubble) {
         std::cout << "Kesimpulan: **Insertion Sort lebih efisien** untuk data ini (jumlah langkah lebih sedikit).\n";
    } else {
        std::cout << "Kesimpulan: Kedua metode memiliki efisiensi yang sama untuk data ini.\n";
    }
    std::cout << "==================================================\n";

    return 0;
}