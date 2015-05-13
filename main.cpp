#include<iostream>
using namespace std;

struct B4
{
    virtual void g(int) {};
};
 
struct D4 : B4
{
    virtual void g(int) {}; // OK
    virtual void g(double) {}; // Error
};
int main()
{
    
}
