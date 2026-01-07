#include <iostream>
using namespace std;

// fungsi tampilkan Array
// ++++++++++++++++++++++
void tampilkanArray(const int arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

// Fungsi insertion Sort
// +++++++++++++++++++++

void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
    cout << "Hasil Pengurutan Step-" << i << ": ";
    tampilkanArray(arr, n);
  }
}

// Fungsi Binary Search
// +++++++++++++++++++=

int binarySearch(int arr[], int n, int target) {
  int low = 0, high = n - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] == target)
      return mid;  // ditemukan
    else if (arr[mid] < target)
      low = mid + 1;  // cari di kanan
    else
      high = mid - 1;  // cari di kiri
  }
  return -1;  // Tidak ditemukan
}

//      Main
//+++++++++++++++
int main() {
  // data awal dari soal
  int ContohData[] = {2, 3, 12, 43, 54, 65, 22, 76, 33, 64, 123, 543};
  int JumlahData = sizeof(ContohData) / sizeof(ContohData[0]);

  cout << "============================================\n";
  cout << "DATA YANG AKAN DIGUNAKAN: ";
  tampilkanArray(ContohData, JumlahData);
  cout << "++++++++++++++++++++++++++++++++++++++++++++\n\n";

  int n;
  cout << "MASUKAN JUMLAH ELEMENT ARRAY: ";
  cin >> n;

  int arr[n];
  cout << "\nsilahkan inputkan elemen array sesuai data di atas :\n";
  for (int i = 0; i < n; i++) {
    cout << "Inputkan elemen array indeks ke-" << i << ": ";
    cin >> arr[i];
  }
  cout << "\n+++++++++++++++++++++++++++++++++++++\n";
  cout << "Data Awal (Hasil Input): ";
  tampilkanArray(arr, n);
  cout << "++++++++++++++++++++++++++++++++++++++++\n";

  // Sort the array
  insertionSort(arr, n);

  cout << "\n+++++++++++++++++++++++++++++++++++++++\n";
  cout << "Data Setelah Diurutkan (Ascending): ";
  tampilkanArray(arr, n);
  cout << "++++++++++++++++++++++++++++++++++++++++++\n";

  int target = 22;
  cout << "\nData Yang Ingin Dicari (Otomatis Sesuai Soal): " << target << endl;

  int index = binarySearch(arr, n, target);
  if (index != -1)
    cout << "Angka ditemukan pada indeks ke-" << index << ": " << arr[index] << endl;
  else
    cout << "Data tidak ditemukan dalam array." << endl;

  cout << "\n+++++++++++++++++++++++++++++++\n";
  cout << "Data Akhir Setelah Proses Sorting: ";
  tampilkanArray(arr, n);
  cout << "++++++++++++++++++++++++++++++++++\n";

  return 0;
}
