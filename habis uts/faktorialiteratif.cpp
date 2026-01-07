#include <iostream>
using namespace std;

int main() {
    int n;
    long long hasil = 1;

    cout << "Masukkan n: ";
    cin >> n;

    if (n < 0) {
        cout << "Faktorial tidak terdefinisi untuk bilangan negatif.";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        hasil *= i;
    }

    cout << n << "! = " << hasil;
    return 0;
}