#pragma once
#include<functional>
#include"tcp_socket.hpp"

typedef std::function<void (const std::string& req,std::string* resp)> Handler;
class TcpServer
{
public:
    TcpServer(const std::string& ip,uint16_t port)
        :ip_(ip)
        ,port_(port)
    {}
    
    bool Start(Handler handler)
    {
        //
        CHECK_RET(listen_sock_.Socket());
        CHECK_RET(listen_sock_.Bind(ip_,port_));
        CHECK_RET(listen_sock_.Listen(5));
        for(;;)
        {
            TcpSocket new_sock;
            std::string ip;
            uint16_t port=0;
            if(!listen_sock_.Accept(&new_sock,&ip,&port))
            {
                continue;
            }
            printf("[client %s:%d] connect!\n",ip.c_str(),port);
            for(;;)
            {
            
                std::string req;
                bool ret=new_sock.Recv(&req);
                if(!ret)
                {
                
                
                    printf("[client %s:%d] disconnect!\n",ip.c_str(),port);
                    new_sock.Close();
                    break;
                }
                std::string resp;
                handler(req,&resp);
                new_sock.Send(resp);


                printf("[%s:%d] req:%s,resp:%s\n",ip.s_str(),port,req.c_str(),resp.c_str());
            }
        }
        return true;
    }
i
private:
    Tcpsocket listen_sock_;
    std::string ip_;
    uint64_t port_;
}
