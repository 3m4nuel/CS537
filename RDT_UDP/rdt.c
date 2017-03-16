#include "rdt.h"

int rdt_socket(int address_family, int type, int protocol)
{
    return socket(address_family, type, protocol);
}

int rdt_bind(int socket_descriptor, const struct sockaddr *local_address, socklen_t address_length)
{
    return bind(socket_descriptor, local_address, address_length);
}

int rdt_recv(int socket_descriptor, char *buffer, int buffer_length, int flags, struct sockaddr *from_address, int *address_length)
{
    return recvfrom(socket_descriptor, buffer, buffer_length, flags, from_address, address_length);
}

int rdt_sendto(int socket_descriptor, char *buffer, int buffer_length, int flags, struct sockaddr *destination_address, int address_length)
{
    return sendto(socket_descriptor, buffer, buffer_length, flags, destination_address, address_length);
}

int rdt_close(int fildes)
{
    return close(fildes);
}
