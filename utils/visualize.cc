#include <bits/stdc++.h>

using namespace std;
typedef uintptr_t usize;

int main() {
    usize n;
    cin >> n;
    string colors[] = {"indigo", "yellow", "blue", "red", "green"};
    string out = "<svg height='210' width='500'>\n";
    for (usize polygon = 1; polygon <= n; polygon++) {
        out += "<polygon points='";
        usize vertices;
        cin >> vertices;
        while (vertices--) {
            double x, y;
            cin >> x >> y;
            out += to_string(x * 10) + "," + to_string(y * -10) + " ";
        }
        out += "' style='fill:";
        out += colors[(polygon - 1) % (sizeof(colors) / sizeof(colors[0]))];
        out += ";stroke:black;stroke-width:0.1' />\n";
    }
    out += "</svg>";
    freopen("image.svg", "w", stdout);
    cout << out << endl;
}
