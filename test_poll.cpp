#include<cstdio>
#include<poll.h>
int main(){

    int time_out = 10000;
	int result, poll_ok = 0;

    poll_ok = poll(NULL, 0, time_out);
    int i = poll_ok;
}
