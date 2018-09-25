
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

// struct frame {
//     // int a;
//     // int b;
//     string s;
// } ;


class frame 
{
    public :
    int a ;
    int b;
    string s;
    frame(){
        a = 0;
        b=4;
        s = "";
    }

};

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
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    // cout<<"above gen";
    // string s= generate_packet();
    // cout<<"below gen";
    // cout<<"s="<<s<<endl;
    // char c[s.length()];
    // strcpy(c, s.c_str());
    // int a[2]={2475,153};
    frame r;
    r.a = 12;
    r.b = 23;
    // r.s = '8';
    r.s = "here";
    // strcpy(r.s, "here");
    // printf("%s",r.s);
    cout<<r.s;
    send(sock , &r , sizeof(r) , 0 );
    printf("Hello message sent\n"); 
    // valread = read( sock , buffer, 1024); 
    // printf("%s\n",buffer );
    return 0; 
} 