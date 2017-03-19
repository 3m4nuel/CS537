#ifndef RDT_H_INCLUDED
#define RDT_H_INCLUDED

#include <netinet/in.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PACKET_SIZE 516 // size of the struct packet

int server_port;

// need to fix rdt.c sizes
struct packet {
    uint16_t id;
    uint16_t srcPort;
    uint16_t dstPort;
    uint16_t cksum;
    uint16_t len;
    uint16_t full_data_sz;
    uint32_t ackno;
    uint32_t seqno;
    char data[500];
};

typedef struct packet packet_t;

struct pkt_hldr {
    int id;
    int full_data_sz;
    packet_t pkt_list[100]; // needs to be a stack // need to determine a better max pkt list size.
};

typedef struct pkt_hldr pkt_hldr_t;

int rdt_socket(int address_family, int type, int protocol);

int rdt_bind(int socket_descriptor, const struct sockaddr *local_address, socklen_t address_length);

int rdt_recv(int socket_descriptor, char *buffer, int buffer_length, int flags, struct sockaddr *from_address, int *address_length);

int rdt_sendto(int socket_descriptor, char *buffer, int buffer_length, int flags, struct sockaddr *destination_address, int address_length);

int rdt_close(int fildes);

#endif // RDT_H_INCLUDED
