// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>   // For FILE, perror, printf, etc.
#include <stdlib.h>  // For free, malloc, etc.
#include <unistd.h>  // For close, read, etc.
#include <sys/socket.h>  // For socket functions
#include <arpa/inet.h>  // For sockaddr_in, INADDR_ANY, etc.
#include <string.h>  // For memset, etc.
#include <stddef.h>  // For size_t
#include <pthread.h> // Include the pthread header


#define BUFFER_SIZE 2057
#define PORT 8080

extern char pid_buffer[BUFFER_SIZE];  // Declare as external

int setup_socket();
int fetch_pid();
int get_pid(char *buffer, size_t buffer_size);
void *handle_volte(void *arg);  // Ensure the correct prototype
void handle_sipp(int socket);



#endif
