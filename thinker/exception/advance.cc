#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> data(10);
    vector<int>::iterator pos = data.begin();
    advance(pos,10);
    if(pos == data.end())
        cout << "nb" << endl;
}
