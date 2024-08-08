#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"

#define PORT 8080

char pid_buffer[BUFFER_SIZE];

int setup_socket() {
    int server_fd;
    int opt = 1;
    struct sockaddr_in address;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        return -1;
    }

    return server_fd;
}

int fetch_pid(char *process) {
    char path[BUFFER_SIZE];
    snprintf(path, BUFFER_SIZE, "ps -ef | grep \"./%s\" | grep -v \"grep\" | grep -v \"vim\" | grep -v \"vi\" | awk '{ print $2 }'", process);

    FILE *fp = popen(path, "r");
    if (fp == NULL) {
        perror("popen");
        return -1;
    }

    if (fgets(pid_buffer, sizeof(pid_buffer), fp) != NULL) {
        printf("Fetched PID: %s\n", pid_buffer);
        pclose(fp);
        return atoi(pid_buffer);
    }

    pclose(fp);
    return -1;
}

void handle_sipp(int socket) {
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    if (valread < 0) {
        perror("read");
        close(socket);
        return;
    }

    // Perform actions specific to SIPp calls
    printf("Handling SIPp Call: %s\n", buffer);
    close(socket);
}

int get_pid(char *buffer, size_t buffer_size) {
    // Your implementation here
    return 0;
}
