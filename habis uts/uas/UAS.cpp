#include <iostream>
using namespace std;

int main() {
    string nama[50];
    int harga[50], jumlah[50];
    int pilihan, index = 0;
    int totalBelanja, totalDiskon, totalBayar;

    do {
        cout << "\n=== KASIR MINIMARKET ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Belanja\n";
        cout << "3. Bayar\n";
        cout << "4. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Nama Barang   : ";
                cin >> nama[index];
                cout << "Harga Barang  : ";
                cin >> harga[index];
                cout << "Jumlah Barang : ";
                cin >> jumlah[index];
                index++;
                break;

            case 2:
                cout << "\n--- DAFTAR BELANJA ---\n";
                for (int i = 0; i < index; i++) {
                    cout << i + 1 << ". " << nama[i]
                         << " | Harga: " << harga[i]
                         << " | Jumlah: " << jumlah[i] << endl;
                }
                break;

            case 3:
                totalBelanja = 0;
                for (int i = 0; i < index; i++) {
                    totalBelanja += harga[i] * jumlah[i];
                }

                totalDiskon = 0;

                if (totalBelanja >= 100000) {
                    totalDiskon = totalBelanja * 0.1; // 10% diskon
                }

                totalBayar = totalBelanja - totalDiskon;

                cout << "\nTotal Belanja : Rp " << totalBelanja << endl;
                cout << "Total Diskon  : Rp " << totalDiskon << endl;
                cout << "Total Bayar   : Rp " << totalBayar << endl;
                cout << "Terima kasih telah berbelanja!\n";
                break;

            case 4:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Menu tidak valid!\n";
        }
    } while (pilihan != 4);

    return 0;
}