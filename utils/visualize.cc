#include <bits/stdc++.h>

using namespace std;
typedef uintptr_t usize;

int main() {
    usize n;
    cin >> n;
    string colors[] = {"indigo", "yellow", "blue", "red", "green"};
    double minx, miny, maxx, maxy;
    vector<vector<pair<double, double>>> polygons(n);
    for (usize i = 0; i < n; i++) {
        usize n_vertices;
        cin >> n_vertices;
        vector<pair<double, double>> vertices;
        while (n_vertices--) {
            double x, y;
            cin >> x >> y;
            minx = min(x, minx);
            miny = min(y, miny);
            maxx = max(x, maxx);
            maxy = max(y, maxy);
            vertices.push_back(make_pair(x, y));
        }
        polygons[i] = vertices;
    }

    auto rangex = maxx - minx, rangey = maxy - miny;
    auto scalex = 1920.0 / rangex, scaley = 1080.0 / rangey;
    auto scale = min(scalex, scaley);
    string out =
        "<html><body><img><svg height='1080' width='1920' viewbox='0 " +
        to_string(-maxy * scale) + " 1920 1080'>\n";
    for (usize i = 0; i < n; i++) {
        out += "<polygon points='";
        for (auto vertex : polygons[i]) {
            auto x = vertex.first;
            auto y = vertex.second;
            x -= minx;
            y -= miny;
            x *= scale, y *= scale;
            out += to_string(x) + "," + to_string(-y) + " ";
        }
        out += "' style='fill:";
        out += colors[i % (sizeof(colors) / sizeof(colors[0]))];
        out += ";stroke:black;stroke-width:0.1' />\n";
    }
    out += "</svg></img></body></html>";
    freopen("image.html", "w", stdout);
    cout << out << endl;
}
