#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include "TestSuite.h"

using namespace std;

//继承后，实现run即可
class TestVector : public TestSuite::Test
{
    public:
        void run() {
            test_pushback();           
        } //void run()
    private:
        void test_pushback()
        {
            bool flag = false;
            v.push_back(4);
            test_(v.front() == 4);          
            test_(v.back() == 4);
            v.pop_back();
            test_(v.size() == 0);
            try {
                v.at(2);    
            }catch(out_of_range &what)
            {
                    flag = true;
            }
            test_(flag == true);
        }
        vector<int> v;

               
};

int main()
{
        TestVector tvector;
        tvector.run();
        tvector.report();
}
