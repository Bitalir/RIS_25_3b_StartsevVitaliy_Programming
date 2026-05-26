#include <iostream>
using namespace std;

void Merge(int* start1, int* end1, int* start2, int* end2) {
    int* start = start1;
    int* end = end2;
    int* rez = new int[end - start + 1];
    int i = 0;

    while (start1 <= end1 && start2 <= end2) {
        if (*start1 < *start2) {
            rez[i] = *start1;
            start1++;
        }
        else {
            rez[i] = *start2;
            start2++;
        }
        i++;
    }

    for (; i < end - start + 1; i++) {
        if (start1 <= end1) {
            rez[i] = *start1;
            start1++;
        }
        else {
            rez[i] = *start2;
            start2++;
        }
    }

    for (int j = 0; j < end - start + 1; j++) {
        *(start + j) = rez[j];
    }

    delete[] rez;
}

void Sort(int* start, int* end) {
    if (start < end) {
        int* mid = start + (end - start) / 2;
        Sort(start, mid);
        Sort(mid + 1, end);
        Merge(start, mid, mid + 1, end);
    }
}

int main() {
    int a = { 3, 5, 1, 4, 9, 6, 12, 32, -1, 0 };
    Sort(a, a + 9);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < 10; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
