#include<cstdio>

void func1(){
    static int i=1;
    i++;
}


void func2(){
    static int i=1;
    i++;
}


int main(){
    func1();
    func2();
    func1();
    func2();

}
