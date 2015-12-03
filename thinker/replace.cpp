#include <cassert>
#include <cstddef>
#include <string>

using namespace std;

void replaceChars(string& modtifyMe,const string& findMe,
                　const string& newChars) {
    size_t i = modtifyMe.find(findMe,0);
    if (i != string::nops)
        modtifyMe.replace(i,findMe.size(),newChars);
}

int main()
{
    string bigNews = "I thought I saw Elvis in a UFO."
                     "I have been working too hard.";
    string replacement("wig");
    string findMe("UFO");
    
    replaceChars(bigNews,findMe,replacement);
    assert(bigNews == "I thought I saw Elvis in a "
                      "wig. I have been working too hard");    
    
    
}
                
