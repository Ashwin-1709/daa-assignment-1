#ifndef DBG_H
#define DBG_H
#include "typedefs.hh"
#include <bits/stdc++.h>
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template <typename T_container,
          typename T = typename std::enable_if<
              !std::is_same<T_container, std::string>::value,
              typename T_container::value_type>::type>
std::ostream &operator<<(std::ostream &os, const T_container &v) {
    os << '{';
    std::string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
template <typename T> void debug_out(std::string s, T t) {
    std::cout << "[" << s << ": " << t << "]\n";
}
template <typename T, typename... U>
void debug_out(std::string s, T t, U... u) {
    usize w = 0, c = 0;
    while (w < s.size()) {
        if (s[w] == '(')
            c++;
        if (s[w] == ')')
            c--;
        if (!c and s[w] == ',')
            break;
        w++;
    }
    std::cout << "[" << s.substr(0, w) << ": " << t << "] ";
    debug_out(s.substr(w + 2, s.size() - w - 1), u...);
}
#define dbg(x...) debug_out(#x, x)

#endif
