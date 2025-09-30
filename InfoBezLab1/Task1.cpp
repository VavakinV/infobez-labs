#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool next_permutation(vector<char>& a) {
    int n = a.size();
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i < 0) return false;
    int j = n - 1;
    while (a[j] <= a[i]) j--;
    swap(a[i], a[j]);
    int l = i + 1, r = n - 1;
    while (l < r) swap(a[l++], a[r--]);
    return true;
}

void task1() {
    ofstream fout("output.txt");

    vector<char> s = { '2','2','5','5','7','7','7','7' };

    for (int i = 0; i < (int)s.size(); i++) {
        for (int j = i + 1; j < (int)s.size(); j++) {
            if (s[j] < s[i]) swap(s[i], s[j]);
        }
    }

    do {
        for (char c : s) fout << c;
        fout << '\n';
    } while (next_permutation(s));

    fout.close();
}