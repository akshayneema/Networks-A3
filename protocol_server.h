#ifndef PROTOCOL_SERVER_H
#define PROTOCOL_SERVER_H

// #define MAX_SEQ 7
typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

// #define MAX_PKT 1024 /* determines packet size in bytes */
// typedef enum {false, true} boolean; /* boolean type */

#include <bits/stdc++.h>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <fcntl.h>
using namespace std;


typedef struct { /* frames are transported in this layer */
int seq; /* sequence number */
int ack; /* acknowledgement number */
string info; /* the network layer packet */
} frame;

string generate_packet();
string encodeString(frame f);
void buildFrame(string s);


static bool between(int a,int b,int c);

void wait_for_event(event_type& event, int& sock);

void send_data(int frame_nr,int frame_expected,string* framebuffer,int sock);

void go_back_n(int& sock);

void enable_network_layer();

void disable_network_layer();

#endif

