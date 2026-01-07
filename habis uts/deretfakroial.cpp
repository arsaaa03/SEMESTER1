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

    if (n < 1) {
        cout << "n harus minimal 1.";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        cout << i << "! = " << faktorial(i) << endl;
    }

    return 0;
}