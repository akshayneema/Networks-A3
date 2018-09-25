
// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <bits/stdc++.h>
#define PORT 8080 
using namespace std;

// struct frame{
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
    int frame_expected=0%7;
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
    int arr[2] = {0,0};
    // valread = read( new_socket , buffer, 1024);
    frame rcv;
    // rcv.a=4;
    // rcv.b = 0;
    rcv.s= "hi";
    cout<<rcv.s;
    valread = read( new_socket , &rcv, sizeof(rcv));
    // valread = recv(new_socket, &rcv, sizeof(rcv), 0);
    // if(buffer is same as frame expected)
    // {
        // frame_expected=(frame_expected+1)%7;
        // printf("%s\n",buffer ); 
        // int a=sizeof(buffer);
        // printf("%d",arr[0]);
        // printf("%d",arr[1]);
        // string str = rcv.s;
        // printf("%d\n",rcv.a);
        cout<<rcv.a<<endl;
        cout<<rcv.b<<endl;
        // printf("%d\n",rcv.b);
        // string str = rcv.s;
        // printf("%s\n",str);
        // int n = sizeof(str);
        // int n = str.length();
        cout<<rcv.s;
        // send(new_socket , hello , strlen(hello) , 0 ); 
        // printf("Hello message sent\n"); 
        cout<<"fbhsjf"<<endl;
    // }
    
    return 0; 
} 