#include <cstdint>
#include <iostream>
#include <vector>
typedef uintptr_t usize;
/// @brief Given data of Initial and Decomposed Polygon , It Generates Drawable
/// HTML Code for Polygon Visualization
int main() {
    usize num_vertices_initial;
    std::vector<double> initial_x, initial_y;
    std::cin >> num_vertices_initial;
    for (usize i = 0; i < num_vertices_initial; i++) {
        double x, y;
        std::cin >> x >> y;
        initial_x.push_back(x);
        initial_y.push_back(y);
    }
    usize n;
    std::cin >> n;
    std::string colors[] = {"#a7d52a", "#dff429", "#f6c137", "#f25e40",
                            "#c32a94", "#7328b6", "#3438bd", "#3f77c4",
                            "#4daecf", "#52c67f", "#79c725"};
    double minx, miny, maxx, maxy;
    std::vector<std::vector<std::pair<double, double>>> polygons(n);
    for (usize i = 0; i < n; i++) {
        usize n_vertices;
        std::cin >> n_vertices;
        std::vector<std::pair<double, double>> vertices;
        while (n_vertices--) {
            double x, y;
            std::cin >> x >> y;
            minx = std::min(x, minx);
            miny = std::min(y, miny);
            maxx = std::max(x, maxx);
            maxy = std::max(y, maxy);
            vertices.push_back(std::make_pair(x, y));
        }
        polygons[i] = vertices;
    }
    auto rangex = maxx - minx, rangey = maxy - miny;
    auto scalex = 1920.0 / (rangex * 2), scaley = 1080.0 / (rangey * 2);
    auto scale = std::min(scalex, scaley);
    std::string out =
        "<html><body><img style='display:flex';><svg height='540' "
        "width='960' viewbox='0 " +
        std::to_string(-rangey * scale) + " 960 540'>\n<polygon points='";

    for (usize i = 0; i < num_vertices_initial; i++) {
        auto x = initial_x[i];
        auto y = initial_y[i];
        x -= minx;
        y -= miny;
        x *= scale, y *= scale;
        out += std::to_string(x) + "," + std::to_string(-y) + " ";
    }
    out += "' style='fill:teal;stroke:black;stroke-width:1'/>\n</svg>\n<svg "
           "height='540' width='960' viewbox='0 " +
           std::to_string(-rangey * scale) + " 960 540'>\n";
    for (usize i = 0; i < n; i++) {
        out += "<polygon points='";
        for (auto vertex : polygons[i]) {
            auto x = vertex.first;
            auto y = vertex.second;
            x -= minx;
            y -= miny;
            x *= scale, y *= scale;
            out += std::to_string(x) + "," + std::to_string(-y) + " ";
        }
        out += "' style='fill:";
        out += colors[i % (sizeof(colors) / sizeof(colors[0]))];
        out += ";stroke:black;stroke-width:1' />\n";
    }
    out += "' style='fill:teal;stroke:black;stroke-width:1'/>\n</svg>\n<svg "
           "height='540' width='960' viewbox='0 " +
           std::to_string(-rangey * scale) + " 960 540'>\n";
    usize n_merge;
    std::cin >> n_merge;
    for (usize i = 0; i < n_merge; i++) {
        out += "<polygon points='";
        usize cur;
        std::cin >> cur;
        while (cur--) {
            double x, y;
            std::cin >> x >> y;
            x -= minx;
            y -= miny;
            x *= scale, y *= scale;
            out += std::to_string(x) + "," + std::to_string(-y) + " ";
        }
        out += "' style='fill:";
        out += colors[i % (sizeof(colors) / sizeof(colors[0]))];
        out += ";stroke:black;stroke-width:1' />\n";
    }
    out += "</svg></img></body></html>";
    freopen("image.html", "w", stdout);
    std::cout << out << std::endl;
}
