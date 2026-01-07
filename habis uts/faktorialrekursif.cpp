#include <iostream>
using namespace std;

long long faktorial(int n) {
    if (n <= 1)
        return 1;
    return n * faktorial(n - 1);
}

int main() {
    int n;
    cout << "Masukkan n: ";
    cin >> n;

    if (n < 0) {
        cout << "Faktorial tidak terdefinisi untuk bilangan negatif.";
        return 0;
    }

    cout << "Faktorial dari " << n << " adalah " << faktorial(n);
    return 0;
}