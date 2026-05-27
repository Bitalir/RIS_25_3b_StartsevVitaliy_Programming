#include <iostream>
#include <clocale>
using namespace std;
int n;
int arr[100];

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Введите размер массива";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    bool f = false;
    for (int i = 0; i < n - 1; ++i) {
        f = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                f = true;
            }
        }
        for (int k = 0; k < n; ++k) {
            cout << arr[k] << " ";
        }
        cout << endl;

        if (!f) {
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}