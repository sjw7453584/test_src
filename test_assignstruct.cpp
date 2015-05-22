#include<cstdio>
typedef struct stA{
    int a;
    int b;
}stA_t;

stA_t g_st={
 a:1,b:2
        };
int main(){
    printf("%d\n%d",g_st.a, g_st.b);
}
