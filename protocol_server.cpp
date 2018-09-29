#define MAX_SEQ 7
#include "protocol_server.h"
// typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

#include <bits/stdc++.h>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

using namespace std;
const double threshold=0.0003;

clock_t start_timer[MAX_SEQ+1];
clock_t start_time;

frame gb_recv;

int enable=1;


string generate_packet()
{
	srand(time(0));
    int length=rand()%64+10;
    // cout<<"l="<<length<<endl;
    char c[length];
    memset(c,'0',length);
    // cout<<"c(1)="<<c<<endl;
    string s;
    s=c;
    return s;
}

string encodeString(frame f)
{
    string seqno=to_string(f.seq);
    string ackno=to_string(f.ack);
    return seqno+ackno+f.info+"\0";
    
}

void buildFrame(string s)
{
    // frame f;
	
		gb_recv.seq=s[0]-48;
		gb_recv.ack=s[1]-48;
		int len=s.length();
		gb_recv.info= s.substr(2,len-4);
	
    // return f;
}


static bool between(int a,int b,int c)
{
	/* Return true if a <= b < c circularly; false otherwise. */
	if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return(true);
	else
		return(false);
}


void wait_for_event(event_type& event, int& sock)
{
	// int valread = read(sock,buffer,2026);

	while(true){

		for(int i=0;i<8;i++){
			if(start_timer[i]!=0){
				clock_t end = clock();
				double time_elapsed = (double)(end-start_timer[i])/CLOCKS_PER_SEC;
				if(time_elapsed>=threshold){
					event = timeout;
					return;
				}
			}
		}

		char str[1024]={0};
		int valread = read(sock,str,1024);

		

		// cout<<"          waiting"<<endl;
		

		

		

		
		if(valread!=-1 && valread!=0){

			cout<<"valread         " <<valread<<endl;

			cout<<"str    "<<str<<endl;

			string ss = str;

			buildFrame(ss);
			
			event = frame_arrival;
			return;
		}

		clock_t end = clock();

		double time_passed = (double)(end-start_time)/CLOCKS_PER_SEC;

		if(time_passed>=0.025){
			event = network_layer_ready;
			start_time = clock();
			return;
		}
	}

	
}

void enable_network_layer()
{
	enable=1;
	return;

}

void disable_network_layer()
{
	enable=0;
	return;
}

void send_data(int frame_nr,int frame_expected,string* framebuffer,int sock)
{
	// cout<<"enetered send_data"<<endl;
	frame s;
	// s.info = generate_packet();
	// framebuffer.push(s.info);
	s.info = framebuffer[frame_nr];
	s.seq = frame_nr;
	s.ack = (frame_expected+MAX_SEQ)%(MAX_SEQ+1);
	// cout<<"started encoding"<<endl;
	string str = encodeString(s);
	// cout<<"out of encoding"<<endl;
	char ch[str.length()];
	strcpy(ch,str.c_str());
	// cout<<"started send"<<endl;
	int send_packet = send(sock,ch,strlen(ch),0);
	// cout<<"out of send data"<<endl;
	start_timer[frame_nr] = clock();

	return;

	
}



void go_back_n(int& sock)
{
	int next_frame_to_send;
	int ack_expected;
	int frame_expected;
	frame r;
	// queue<string> framebuffer;
	string framebuffer[MAX_SEQ+1];
	for(int i=0;i<MAX_SEQ+1;i++){
		framebuffer[i] = "0";
	}
	int nbuffered;
	event_type event;

	enable_network_layer();
	ack_expected=0;
	next_frame_to_send=0;
	frame_expected=0;
	nbuffered=0;

	for(int i=0;i<MAX_SEQ+1;i++){
		start_timer[i] = 0;
	}

	int n=0;

	start_time = clock();

	while(true)
	{
		// n++;
		wait_for_event(event,sock);

		// if(enable==0) event=frame_arrival;
		// event = network_layer_ready;

		switch(event)
		{
			case network_layer_ready:{
				
				// from_network_layer(&framebuffer);

				// framebuffer.push()
				if(enable==0) break;
				nbuffered++;
				// string sz = generate_packet();
				// framebuffer.push(sz);
				cout<<"data send"<<endl;
				framebuffer[next_frame_to_send] = generate_packet();
				cout<<"frame    "<<framebuffer[next_frame_to_send];

				send_data(next_frame_to_send,frame_expected,framebuffer,sock);
				// char *st = "hello";
				// cout<<st<<endl;
				// int senddat = send(sock,st, strlen(st),0);


				cout<<"sending     "<<next_frame_to_send<<endl;
				//////////implement send data


				next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				break;
			}

			case frame_arrival:{
				// from_physical_layer(&r);
				// cout<<"data received"<<endl;
				
				if(gb_recv.seq == frame_expected){
					// to_network_layer(&r.info);
					cout<<"data     "<<frame_expected<<endl;
					frame_expected = (frame_expected+1)%(MAX_SEQ+1);

					
				}

				while(between(ack_expected,gb_recv.ack,next_frame_to_send)){
					nbuffered--;
					// stop_timer(ack_expected);

					cout<<n<<endl;

					cout<<"ack_received    "<<ack_expected<<endl;
					start_timer[ack_expected] = 0;
					/////implement stop timer
					ack_expected = (ack_expected+1)%(MAX_SEQ+1);
				}

				break;
			}

			case cksum_err :{ break;}

			case timeout:{
				next_frame_to_send = ack_expected;
				for(int i=1;i<=nbuffered;i++){
					// send_data(next_frame_to_send,frame_expected,framebuffer,sock);
					///////////////////////////
					next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				}
				break;
			}
		}

		// if(n>100) break;

		if(nbuffered<MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();
	}
}
