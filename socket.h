#ifndef SOCKET_H
#define SOCKET_H
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#define PORT 8081
using namespace std;
class Socket {
private:
    int Puerto=8080;
    int sock = 0;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char char_array;
    struct sockaddr_in serv_addr;
public:
    Socket();
    string enviar(string Mensaje,int puerto,string ip, bool);
    static Socket &getInstance(){
        static Socket instance;
        return instance;
    }
    string escuchar2(int puerto);
};


#endif //UNTITLED1_SOCKET_H
