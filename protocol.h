#define MAX_PKT 1024 /* determines packet size in bytes */
// typedef enum {false, true} boolean; /* boolean type */



typedef struct { /* frames are transported in this layer */
int seq; /* sequence number */
int ack; /* acknowledgement number */
string info; /* the network layer packet */
} frame;

static bool between(int a,int b,int c);

static void send_data(int frame_nr,int frame_expected,string buffer[ ]);

void go_back_n();

void enable_network_layer();

void wait_for_event();




