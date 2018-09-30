#define MAX_SEQ 7
#include "protocol.h"
// typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

#include <bits/stdc++.h>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <random>
using namespace std;
const double threshold= 0.15;

clock_t start_timer[MAX_SEQ+1];

frame gb_recv;

int enable=1;

clock_t start_time;


string generate_packet()
{
	// srand(time(0));
    int length=rand()%100+3;
    // cout<<"l="<<length<<endl;
    char c[length];
	for(int i=0;i<length;i++)
	{
		// double p= ((double) rand() / (RAND_MAX));;
		// if(p<0.5)
		// 	c[i]='0';
		// else
		// 	c[i]='1';
		

		


		int a = rand()%2;
		c[i] = a+48;
	}

	int b = rand()%length;
	if(c[b]='0') c[b]='1';
	else c[b] = '0';
    // memset(c,'0',length);
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
		gb_recv.info= s.substr(2,len-2);
	
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

		for(int i=0;i<MAX_SEQ+1;i++){
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

			// cout<<"valread         " <<valread<<endl;

			// cout<<"str    "<<str<<endl;

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
	cout<<"ack_send: "<<s.ack<<endl;

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

	int rnd = rand()%100 +1;

	int num_error = 0;
	int num_recv = 0;
	int m=0;

	clock_t perf_start = clock();

	while(true)
	{
		// n++;
		wait_for_event(event,sock);

		// if(enable==0) event=frame_arrival;
		// char str[1024]={0};
		// int m=0;
		// while(1){
		// 	m++;
		// int valread = read(sock,str,1024);
		// if(valread!=-1 && valread!=0){
		// 	cout<<"str    "<<str<<endl;
		// 	cout<<"m  "<<m<<endl;
		// 	m=0;
		// 	break;
		// }
	// }

		// event = cksum_err;

		
		

		switch(event)
		{
			case network_layer_ready:
				
				// from_network_layer(&framebuffer);

				// framebuffer.push()
				if(enable==0) break;
				nbuffered++;
				// string sz = generate_packet();
				// framebuffer.push(sz);
				cout<<"data send:   "<<endl<<endl;
				framebuffer[next_frame_to_send] = generate_packet();

				// usleep(5000);

				send_data(next_frame_to_send,frame_expected,framebuffer,sock);

				// cout<<"sending     "<<next_frame_to_send<<endl;
				//////////implement send data

				cout<<"seq: "<<next_frame_to_send<<endl;
				cout<<"data: "<< framebuffer[next_frame_to_send]<<endl;
				cout<<"--------------------------------------------------------"<<endl;

				n++;


				next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				break;

			case frame_arrival:
				// from_physical_layer(&r);
				// cout<<"data received"<<endl;

				// cout<<"djgfs        "<<gb_recv.seq<<"       "<<gb_recv.ack<<endl;
				if(num_error==0)
				num_recv++;

				if(gb_recv.seq == frame_expected && num_error==1) goto L;

				if(num_error==1) break;

				if(num_recv==rnd){
					num_recv=0;
					num_error=1;
					rnd = rand()%100 +1;
					break;
				}
			
			L:
				num_error=0;

				cout<<"frame_arrival   "<<endl<<endl;

				cout<<"seq: "<<gb_recv.seq<<endl;
				cout<<"ack_rec: "<<gb_recv.ack<<endl;
				cout<<"data: "<<gb_recv.info<<endl;

				cout<<"--------------------------------------------------------"<<endl;

				m++;
				
				if(gb_recv.seq == frame_expected){
					// to_network_layer(&r.info);
					// cout<<"data     "<<frame_expected<<endl;
					frame_expected = (frame_expected+1)%(MAX_SEQ+1);

					
				}

				while(between(ack_expected,gb_recv.ack,next_frame_to_send)){
					nbuffered--;
					// stop_timer(ack_expected);

					// cout<<n<<endl;

					// cout<<"ack_received    "<<ack_expected<<endl;
					start_timer[ack_expected] = 0;
					/////implement stop timer
					ack_expected = (ack_expected+1)%(MAX_SEQ+1);
				}

				break;

			case cksum_err : break;

			case timeout:
				next_frame_to_send = ack_expected;
				for(int i=1;i<=nbuffered;i++){
					send_data(next_frame_to_send,frame_expected,framebuffer,sock);

					cout<<"nbuffered:  "<<nbuffered<<endl;

					cout<<"burst:  "<<endl;

					cout<<"seq: "<<next_frame_to_send<<endl;
				cout<<"data: "<< framebuffer[next_frame_to_send]<<endl;
				cout<<"--------------------------------------------------------"<<endl;

				n++;
				// usleep(5000);

					///////////////////////////
					next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				}
				break;
		}

		// if(n>400) break;

		if(nbuffered<MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();

	clock_t perf_end = clock();
		double time_perf = (double)(perf_end-perf_start)/CLOCKS_PER_SEC;

		if(time_perf>=10) break;
	}

	cout<<"send: "<<n<<endl;
	cout<<"receive: "<<m<<endl;

	

		// 	int m=0;
		// while(1){
		// 	char str[1024] = {0}; 
		// 	// char* str;
		// 	int valread = read(sock,str,1024);

		// 	m++;
		// 	if(valread!=-1 && valread!=0){
		// 		cout<<"str    "<<str<<"   "<<valread<<endl;
		// 		// break;
		// 	}
		// 	if(m==1000) break;
		// }
}
