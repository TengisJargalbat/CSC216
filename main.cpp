#include <iostream>

int gSequence(int n){
    if(n == 0){
        return 0;
    }
    return n - gSequence(gSequence(n-1));
}

int main()
{
    int g1 = gSequence(1);
    int g2 = gSequence(2);
    int g3 = gSequence(3);
    std::cout << g1 << '\n';
    std::cout << g2 << '\n';
    std::cout << g3 << '\n';
    return 0;
}

