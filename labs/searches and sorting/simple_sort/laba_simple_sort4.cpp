#include <iostream>
#include <vector>
using namespace std;

void Sort(vector<int>& arr, int k) {
    if (k != 0) {
        vector<vector<int>> buckets;
        int j = 0;
        for (int i = 0; i < arr.size() / k; i++) {
            buckets.push_back(vector<int>());
            for (int f = 0; f < k; f++, j++) {
                buckets.back().push_back(arr[j]);
            }
        }
        if (arr.size() % k) {
            buckets.push_back(vector<int>());
            for (; j < arr.size(); j++) {
                buckets.back().push_back(arr[j]);
            }
        }
        for (int i = 0; i < buckets.size(); i++) {
            Sort(buckets[i], k - 1);
        }

        for (int i = 0; i < arr.size(); i++) {
            int x = 0;
            int min = 0;
            for (int f = 0; f < buckets.size(); f++) {
                if (!buckets[f].empty()) {
                    min = buckets[f].front();
                    break;
                }
            }
            for (int f = 0; f < buckets.size(); f++) {
                if (!buckets[f].empty()) {
                    if (buckets[f].front() <= min) {
                        min = buckets[f].front();
                        x = f;
                    }
                }
            }
            arr[i] = buckets[x].front();
            buckets[x].erase(buckets[x].begin());
        }
    }
}

int main() {
    vector<int> a = { 3, 5, 1, 4, 9, 6, 12, 32, -1 };
    Sort(a, 5);
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
}
