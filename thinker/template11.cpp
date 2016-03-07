#include <iostream>
#include <cstring>

using std::strcmp;
using std::cout;
using std::endl;

template<class T>
const T& min(const T& a,const T& b) {
    return (a < b) ? a : b;
}

//模板特化
template<>
const char* const& min<const char*>(const char* const& a, const char* const& b) {
    return (strcmp(a,b) < 0) ? a:b;
}

int main() {
    const char *s2 = "say \"Ni-!\"", *s1 = "knights who";
    cout << min(s1,s2) << endl;
    cout << min<>(s1,s2) << endl;
}
