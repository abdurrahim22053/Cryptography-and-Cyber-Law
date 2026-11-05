#ifndef OSI_COMMON_H
#define OSI_COMMON_H

#include <stdint.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define OSI_MAX_MESSAGE 4096
#define OSI_PORT_DEFAULT 5050

static int send_all(int fd, const void *buffer, size_t length) {
    const unsigned char *p = (const unsigned char *)buffer;
    size_t sent = 0;
    while (sent < length) {
        ssize_t n = send(fd, p + sent, length - sent, 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("send");
            return -1;
        }
        if (n == 0) return -1;
        sent += (size_t)n;
    }
    return 0;
}

static int recv_all(int fd, void *buffer, size_t length) {
    unsigned char *p = (unsigned char *)buffer;
    size_t received = 0;
    while (received < length) {
        ssize_t n = recv(fd, p + received, length - received, 0);
        if (n < 0) {
            if (errno == EINTR) continue;
            perror("recv");
            return -1;
        }
        if (n == 0) return -1;
        received += (size_t)n;
    }
    return 0;
}

/* Network byte order, fixed 32-bit length prefix for TCP application framing. */
static int send_frame(int fd, const char *message) {
    uint32_t len = (uint32_t)strlen(message);
    uint32_t wire_len = htonl(len);
    if (send_all(fd, &wire_len, sizeof(wire_len)) < 0) return -1;
    return send_all(fd, message, len);
}

static int recv_frame(int fd, char *buffer, size_t capacity) {
    uint32_t wire_len = 0;
    if (recv_all(fd, &wire_len, sizeof(wire_len)) < 0) return -1;
    uint32_t len = ntohl(wire_len);
    if (len >= capacity || len > OSI_MAX_MESSAGE) {
        fprintf(stderr, "Frame length too large: %u\n", len);
        return -1;
    }
    if (recv_all(fd, buffer, len) < 0) return -1;
    buffer[len] = '\0';
    return (int)len;
}

static void print_stage(const char *side, int layer, const char *name, const char *detail) {
    printf("[%s][L%d] %s: %s\n", side, layer, name, detail);
    fflush(stdout);
}

#endif
