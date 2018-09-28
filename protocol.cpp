#define MAX_SEQ 7
typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready} event_type;

#include <bits/stdc++.h>
#include "protocol.h"
using namespace std;


static bool between(int a,int b,int c)
{
	/* Return true if a <= b < c circularly; false otherwise. */
	if (((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return(true);
	else
		return(false);
}


void wait_for_event()
{

}

void enable_network_layer()
{

}

void from_network_layer()
{

}

void send_data()
{

}

void from_physical_layer(frame r)
{

}

void go_back_n()
{
	int next_frame_to_send;
	int ack_expected;
	int frame_expected;
	frame r;
	queue<string> buffer;
	int nbuffered;
	event_type event;

	enable_network_layer();
	ack_expected=0;
	next_frame_to_send=0;
	frame_expected=0;
	nbuffered=0;

	while(true)
	{
		wait_for_event(&event);

		switch(event)
		{
			case network_layer_ready:
				from_network_layer(&buffer[]);
				nbuffered++;
				send_data(next_frame_to_send,frame_expected,buffer);
				//////////implement send data


				next_frame_to_send = (next_frame_to_send+1)%(MAX_SEQ+1);
				break;

			case frame_arrival:
				from_physical_layer(&r);

		}
	}
}
