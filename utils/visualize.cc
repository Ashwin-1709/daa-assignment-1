#include <bits/stdc++.h>

using namespace std;
typedef uintptr_t usize;

int main() {
    int num_vertices_initial;
    vector<double>  initial_x, initial_y;
    cin >> num_vertices_initial;
    for(int i = 0; i < num_vertices_initial; i++){
        double x, y;
        cin >> x >> y;
        initial_x.push_back(x);
        initial_y.push_back(y);
    }
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
    auto scalex = 1920.0 / (rangex*2), scaley = 1080.0 / (rangey*2);
    auto scale = min(scalex, scaley);
    string out =
        "<html><body><img style='display:flex';><svg height='540' width='960' viewbox='0 " +
        to_string(-rangey * scale) + " 960 540'>\n<polygon points='";

    for(int i = 0; i < num_vertices_initial; i++){
        auto x = initial_x[i];
        auto y = initial_y[i];
        x -= minx;
        y -= miny;
        x *= scale, y *= scale;
        out += to_string(x) + "," + to_string(-y) + " ";
    }
    out += "' style='fill:teal;stroke:black;stroke-width:1'/>\n</svg>\n<svg height='540' width='960' viewbox='0 " +
        to_string(-rangey * scale) + " 960 540'>\n";
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
        out += ";stroke:black;stroke-width:1' />\n";
    }
    out += "</svg></img></body></html>";
    freopen("image.html", "w", stdout);
    cout << out << endl;
}
