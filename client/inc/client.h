#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include  <iostream>

using namespace std;

#define SOCKET_ADDR "/tmp/unix_socket"

typedef struct letters_s {
    char required[26 + 1];
    char optional[26 + 1];
} letters_t;
