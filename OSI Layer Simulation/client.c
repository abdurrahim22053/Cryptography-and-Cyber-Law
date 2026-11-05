#define _POSIX_C_SOURCE 200112L
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "osi_common.h"

static void encapsulate(const char *message) {
    print_stage("CLIENT", 7, "Application", "User message accepted");
    print_stage("CLIENT", 6, "Presentation", "Simulated encoding: UTF-8 text");
    puts("[CLIENT][PROGRESS] 2/7 layers completed"); fflush(stdout);
    print_stage("CLIENT", 5, "Session", "Logical session established");
    print_stage("CLIENT", 4, "Transport", "TCP segment concept: reliable stream");
    puts("[CLIENT][PROGRESS] 4/7 layers completed"); fflush(stdout);
    print_stage("CLIENT", 3, "Network", "IP packet concept: destination address selected");
    print_stage("CLIENT", 2, "Data Link", "Frame concept: local-link delivery");
    puts("[CLIENT][PROGRESS] 6/7 layers completed"); fflush(stdout);
    print_stage("CLIENT", 1, "Physical", "Bit transmission represented by TCP socket send");
    puts("[CLIENT][PROGRESS] 7/7 layers completed"); fflush(stdout);
    printf("[CLIENT][ENCAPSULATED] %s\n", message); fflush(stdout);
}

int main(int argc, char **argv) {
    const char *host = argc > 1 ? argv[1] : "127.0.0.1";
    const char *port = argc > 2 ? argv[2] : "5050";
    const char *message = argc > 3 ? argv[3] : "Hello Server!";
    if (strlen(message) > OSI_MAX_MESSAGE) {
        fprintf(stderr, "Message exceeds %d bytes\n", OSI_MAX_MESSAGE);
        return 1;
    }

    encapsulate(message);

    struct addrinfo hints, *result, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int gai = getaddrinfo(host, port, &hints, &result);
    if (gai != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai));
        return 1;
    }

    int sock = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sock < 0) continue;
        if (connect(sock, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(sock);
        sock = -1;
    }
    freeaddrinfo(result);
    if (sock < 0) {
        fprintf(stderr, "Could not connect to %s:%s. Is the server running?\n", host, port);
        return 1;
    }

    puts("[CLIENT][SOCKET] TCP connection established"); fflush(stdout);
    if (send_frame(sock, message) < 0) {
        close(sock);
        return 1;
    }
    char reply[OSI_MAX_MESSAGE + 1];
    int n = recv_frame(sock, reply, sizeof(reply));
    if (n < 0) {
        fprintf(stderr, "No valid server acknowledgement received\n");
        close(sock);
        return 1;
    }
    printf("[CLIENT][ACK] %s\n", reply);
    puts("[CLIENT][DONE] Transmission completed successfully");
    close(sock);
    return 0;
}
