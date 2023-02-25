#include "dcel.hh"
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
    Point a, b, c;
    a.x = 0;
    a.y = 0;
    b.x = 1;
    b.y = 0;
    c.x = 2;
    c.y = 2;
    cout << angle(a, b, c) << endl;
    // cout << angle(a, c, b) << endl;
    // cout << angle(b, a, c) << endl;
    // cout << angle(b, c, a) << endl;
    // cout << angle(c, a, b) << endl;
    // cout << angle(c, b, a) << endl;
}
