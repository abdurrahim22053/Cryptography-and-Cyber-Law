#define _POSIX_C_SOURCE 200112L
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "osi_common.h"

static void decapsulate(const char *message) {
    print_stage("SERVER", 1, "Physical", "Incoming TCP stream received");
    print_stage("SERVER", 2, "Data Link", "Frame boundary represented by app length prefix");
    puts("[SERVER][PROGRESS] 2/7 layers completed"); fflush(stdout);
    print_stage("SERVER", 3, "Network", "Destination host delivery handled by IP stack");
    print_stage("SERVER", 4, "Transport", "TCP stream reconstructed");
    puts("[SERVER][PROGRESS] 4/7 layers completed"); fflush(stdout);
    print_stage("SERVER", 5, "Session", "Logical session accepted");
    print_stage("SERVER", 6, "Presentation", "UTF-8 text interpreted");
    puts("[SERVER][PROGRESS] 6/7 layers completed"); fflush(stdout);
    print_stage("SERVER", 7, "Application", "Message delivered to user application");
    puts("[SERVER][PROGRESS] 7/7 layers completed"); fflush(stdout);
    printf("[SERVER][RECEIVED] %s\n", message); fflush(stdout);
}

int main(int argc, char **argv) {
    const char *host = argc > 1 ? argv[1] : "127.0.0.1";
    const char *port = argc > 2 ? argv[2] : "5050";
    signal(SIGPIPE, SIG_IGN);

    struct addrinfo hints, *result, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int gai = getaddrinfo(host, port, &hints, &result);
    if (gai != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai));
        return 1;
    }

    int listener = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        listener = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (listener < 0) continue;
        int yes = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
        if (bind(listener, rp->ai_addr, rp->ai_addrlen) == 0 &&
            listen(listener, 8) == 0) break;
        close(listener);
        listener = -1;
    }
    freeaddrinfo(result);
    if (listener < 0) {
        perror("bind/listen");
        return 1;
    }

    printf("[SERVER][LISTENING] %s:%s\n", host, port); fflush(stdout);
    while (1) {
        struct sockaddr_storage peer;
        socklen_t peer_len = sizeof(peer);
        int client = accept(listener, (struct sockaddr *)&peer, &peer_len);
        if (client < 0) {
            if (errno == EINTR) continue;
            perror("accept");
            continue;
        }
        char message[OSI_MAX_MESSAGE + 1];
        int n = recv_frame(client, message, sizeof(message));
        if (n >= 0) {
            decapsulate(message);
            char ack[128];
            snprintf(ack, sizeof(ack), "ACK: received %d bytes", n);
            send_frame(client, ack);
        } else {
            fprintf(stderr, "[SERVER][ERROR] Invalid or interrupted frame\n");
        }
        close(client);
        puts("[SERVER][READY] Waiting for next client..."); fflush(stdout);
    }
    close(listener);
    return 0;
}
