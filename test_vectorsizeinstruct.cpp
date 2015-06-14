#include<vector>
using namespace std;
#include<cstdio>

struct s_test{
    int i;
    int j;
    vector<int> z;
    vector<int> x;

};
int main(){
    int size = sizeof(s_test);
    s_test a;
    int size_o = sizeof(a);
    a.z.push_back(1);
    a.z.push_back(2);
    a.z.push_back(1);
    size_o = sizeof(a);

    a.z.push_back(1);
    a.z.push_back(1);
    a.z.push_back(1);
    size_o = sizeof(a);
    a.z.push_back(1);
    size_o = sizeof(a);
    a.z.push_back(1);
    size_o = sizeof(a);
    a.z.push_back(1);

}
