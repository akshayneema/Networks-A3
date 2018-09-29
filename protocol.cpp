#define MAX_SEQ 7
typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

#include <bits/stdc++.h>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include "protocol.h"
#include <fcntl.h>
using namespace std;

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
	if(s.length()==0)
	{
		f.seq=0;
		f.ack=0;
		f.info="";
	}
	else
	{
		f.seq=s[0];
		f.ack=s[1];
		int len=s.length();
		f.info= s.substr(2,len-2);
	}
    return f;
}

static bool between(int a,int b,int c)
{
	/* Return true if a <= b < c circularly; false otherwise. */
	if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return(true);
	else
		return(false);
}


void wait_for_event(event_type& event, int& sock, queue<string> buffer)
{
	// int valread = read(sock,buffer,2026);

	while(true){

		for(int i=0;i<8;i++){

		}


		int received = fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);

		if(received == -1){
			event = network_layer_ready;
			return;
		}
		else{
			char* str;
			int valread = read(sock,str,2026);
			
			event = frame_arrival;
			return;
		}
	}

	}
}

void enable_network_layer()
{

}

void from_network_layer()
{

}


void to_network_layer(frame info)
{

}

void send_data()
{

}

void from_physical_layer(frame r)
{

}

void to_physical_layer(frame s)
{
	
}


void disable_network_layer()
{

}

void go_back_n(int& sock, char* buffer)
{
	int next_frame_to_send;
	int ack_expected;
	int frame_expected;
	frame r;
	queue<string> framebuffer;
	int nbuffered;
	event_type event;

	enable_network_layer();
	ack_expected=0;
	next_frame_to_send=0;
	frame_expected=0;
	nbuffered=0;

	while(true)
	{
		frame f=wait_for_event(event,sock,buffer);

		switch(event)
		{
			case network_layer_ready:
				from_network_layer(&framebuffer);
				nbuffered++;
				send_data(next_frame_to_send,frame_expected,buffer);
				//////////implement send data


				next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				break;

			case frame_arrival:
				// from_physical_layer(&r);
				r=f;
				if(r.seq == frame_expected){
					to_network_layer(&r.info);
					frame_expected = (frame_expected+1)%(MAX_SEQ+1);
				}

				while(between(ack_expected,r.ack,next_frame_to_send)){
					nbuffered--;
					stop_timer(ack_expected);
					/////implement stop timer

					ack_expected = (ack_expected+1)%(MAX_SEQ+1);
				}

				break;

			case cksum_err : break;

			case timeout:
				next_frame_to_send = ack_expected;
				for(int i=1;i<=nbuffered;i++){
					send_data();
					///////////////////////////
					next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				}
		}

		if(nbuffered<MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();
	}
}
