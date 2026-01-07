#include <iostream>
#include <vector>
using namespace std;

// ============================================
// FUNGSI UNTUK MENAMPILKAN ISI ARRAY
// ============================================
void tampilkanArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// ============================================
// FUNGSI INSERTION SORT
// ============================================
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Geser elemen yang lebih besar ke kanan
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

        // Tampilkan hasil setiap langkah
        cout << "Hasil Pengurutan Step-" << i << ": ";
        tampilkanArray(arr);
    }
}

// ============================================
// FUNGSI BINARY SEARCH
// ============================================
int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid; // Ditemukan
        else if (arr[mid] < target)
            low = mid + 1; // Cari di kanan
        else
            high = mid - 1; // Cari di kiri
    }
    return -1; // Tidak ditemukan
}

int main() {
  
    int ContohData[] = {2, 3, 12, 43, 54, 65, 22, 76, 33, 64, 123, 543};
    int JumlahData = sizeof(ContohData) / sizeof(ContohData[0]);

    cout << "============================================\n";
    cout << "DATA YANG AKAN DIGUNAKAN: ";
    for (int i = 0; i < JumlahData; i++) {
        cout << ContohData[i] << " ";
    }
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++\n\n";

    
    int n;
    cout << "MASUKKAN JUMLAH ELEMEN ARRAY: ";
    cin >> n;

    
    vector<int> arr(n);

    cout << "\nSilakan inputkan elemen array sesuai data di atas:\n";
    for (int i = 0; i < n; i++) {
        cout << "Inputkan elemen array indeks ke-" << i << ": ";
        cin >> arr[i];
    }

    cout << "\n+++++++++++++++++++++++++++++++++++++\n";
    cout << "Data Awal (Hasil Input): ";
    tampilkanArray(arr);
    cout << "++++++++++++++++++++++++++++++++++++++++\n";

    
    insertionSort(arr);

    cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
    cout << "Data Setelah Diurutkan (Ascending): ";
    tampilkanArray(arr);
    cout << "++++++++++++++++++++++++++++++++++++++++++\n";

  
    int target = 22;
    cout << "\nData Yang Ingin Dicari (Otomatis Sesuai Soal): " << target << endl;

    int index = binarySearch(arr, target);
    if (index != -1)
        cout << "Angka ditemukan pada indeks ke-" << index << ": " << arr[index] << endl;
    else
        cout << "Data tidak ditemukan dalam array." << endl;

    cout << "\n+++++++++++++++++++++++++++++++\n";
    cout << "Data Akhir Setelah Proses Sorting: ";
    tampilkanArray(arr);
    cout << "++++++++++++++++++++++++++++++++++\n";

    return 0;
}
