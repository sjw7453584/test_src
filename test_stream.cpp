#include <fstream>
#include <sstream>
#include <iostream>
std::string   trim(std::string st)   
{
	st.erase(0,st.find_first_not_of("\r\t\n "));
	st.erase(st.find_last_not_of("\r\t\n ")+1);
	return   st;
}

int main()
{

    std::ifstream fin;

	fin.open("test.conf", std::ios::in);
    std::string str = "";
    getline(fin, str);
    str = trim(str);

    std::stringstream ss(str);

    std::string name = "", host = "";
    int index, port;
    ss >> index >> name >> host >> port;
    std::cout<<index<<std::endl<<name<<std::endl<<host<<std::endl<<port;
}
