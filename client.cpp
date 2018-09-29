
// Client side C/C++ program to demonstrate Socket programming 
#include <arpa/inet.h>
#include <stdio.h> 
// #include <sys/types.h>
// #include <netdb.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <bits/stdc++.h>
#include <fcntl.h>
#include "protocol.h"
#define PORT 8080 
using namespace std;
// string generate_packet()
// {
//     int length=rand()%1512+512;
//     // cout<<"l="<<length<<endl;
//     char c[length];
//     memset(c,'0',length);
//     // cout<<"c(1)="<<c<<endl;
//     string s;
//     s=c;
//     return s;
// }

// struct frame{
//     string info;
//     int seq;
//     int ack;
//     // string s;
// } ;

// string encodeString(frame f)
// {
//     string seqno=to_string(f.seq);
//     string ackno=to_string(f.ack);
//     return seqno+ackno+f.info;
    
// }

// frame buildFrame(string s)
// {
//     frame f;
//     f.seq=s[0];
//     f.ack=s[1];
//     int len=s.length();
//     f.info= s.substr(2,len-2);
//     return f;
// }

int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "10.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    int status = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);

    if(status==-1){
    	perror("calling fcntl");
    }

    // send(sock , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer ); 

    go_back_n(sock);

    
    
    return 0; 
}