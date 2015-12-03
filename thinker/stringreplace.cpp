#include <cassert>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string s("A piece of text");
    string tag("$tag$");
    s.insert(8,tag + ' ');
    cout << s << endl;
    assert(s == "A piece $tag$ of text");
    int start = s.find(tag);
    assert(start == 8);
    assert(tag.size() == 5);
    s.replace(start,tag.size(),"Hello there");
    assert(s == "A piece Hello there of text");
}
