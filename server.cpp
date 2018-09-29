
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
// #include "protocol.h"
#define PORT 8080 
using namespace std;

string generate_packet()
{
    int length=rand()%1512+512;
    // cout<<"l="<<length<<endl;
    char c[length];
    memset(c,'0',length);
    // cout<<"c(1)="<<c<<endl;
    string s;
    s=c;
    return s;
}

struct frame{
    string info;
    int seq;
    int ack;
    // string s;
} ;

string encodeString(frame f)
{
    string seqno=to_string(f.seq);
    string ackno=to_string(f.ack);
    return seqno+ackno+f.info;
    
}

frame buildFrame(string s)
{
    frame f;
    f.seq=s[0];
    f.ack=s[1];
    int len=s.length();
    f.info= s.substr(2,len-2);
    return f;
}

int caller( int& new_socket , char* buffer)
{
    int valread = read( new_socket , buffer, 1024);
    cout<<valread;
    return valread;
}


int  main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    // valread = read( new_socket , buffer, 1024);
    int l;
    l=caller( new_socket , buffer);
    string buffers=buffer;
    // cout<<"length="<<buffers.length()<<endl;
    // buffers=buffers.substr(0,l);
    // for(int i=0;i<l;i++)
    // {
    //     buffers=buffers+buffer[i];
    // }
    cout<<"buffres="<<buffers<<endl;
    // printf("%s\n",buffer ); 
    //printf madarchod hai...
    l=caller( new_socket , buffer);
    buffers=buffer;
    cout<<"buffres="<<buffers<<endl;
    l=caller( new_socket , buffer);
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    return 0; 
} 