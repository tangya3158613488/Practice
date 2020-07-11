#include<iostream>
#include<unordered_map>
#include"tcp_server.hpp"

std::unordered_map<std::string,std::string> dict;
void Translate(const std::string& req,std::string& resp)
{

    auto it=dict.find(req);
    if(it==dict.end())
    {
        *resp="未找到";
        return;
    }
    *resp=it->second;
    return;
}
int main(int argc,char* argv[])
{
    if(argc!=3)

    {    
       printf("Usage:\n");
        return 1;
    }
    dict.insert(std::make_pair("hello","你好"));
    dict.insert(std::make_pair("apple","苹果"));
    dict.insert(std::make_pair("world","世界"));
    dict.insert(std::make_pair("happy","快乐"));
    dict.insert(std::make_pair("future","未来"));
    TcpServer server(argv[1],atoi(argv[2]));
    server.Start(Translate);
    return 0;
}

