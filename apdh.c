#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handle_apdh(void *arg, char *buffer) {
    int socket = *(int *)arg;
     // Free the allocated memory for the argument

    int bytesRead;

    printf("Client connected.\n");

    // Initial buffer processing
    printf("Received: in APDH file  %s\n", buffer);


    // Extracting data from the buffer sent by main.c
    char source_ip[INET_ADDRSTRLEN], dest_ip[INET_ADDRSTRLEN];
    int source_port, dest_port, max_call, para_call;

    // Assuming the buffer format is: numericValue,sourceIp:sourcePort;destIp:destPort;maxCall

    char *data = strchr(buffer, ',') + 1; // Skip the numericValue part
sscanf(data, "%[^;];%[^:]:%d;%d;%d", source_ip, dest_ip, &dest_port, &max_call, &para_call);

    printf("this is data variable in APHD file%s\n", data);

    char srcip[BUFFER_SIZE];
    snprintf(srcip, BUFFER_SIZE, "%s:%d", source_ip, source_port);
    char destip[BUFFER_SIZE];
    snprintf(destip, BUFFER_SIZE, "%s:%d", dest_ip, dest_port);
    printf("Stored: source data: %s\n", srcip);
    printf("Stored: destination data: %s\n", destip);
    printf("Stored: max_call: %d\n", max_call);
    printf("para call: %d\n",para_call);
    const char *response = "Data received";   //s ip, sport,pcap,input,target,max,para
    write(socket, response, strlen(response));
   char *pcap_file="../APDH_LOAD/pcap/telnet.pcap";
   char *target_file="../APDH_LOAD/exec/TARGET_INFO.txt";



    char run_script[BUFFER_SIZE];
  snprintf(run_script, BUFFER_SIZE, "../APDH_LOAD/exec/APDH_LOADGEN -ip %s -port %d -pcap_file %s -input_file %s -max_call %d -parallel_call %d ",source_ip, dest_port, pcap_file, target_file, max_call, para_call);
    printf("The given Script is: %s\n", run_script);

    printf("Executing command: %s\n", run_script);
    system(run_script);



    printf("Client disconnected.\n");
    close(socket);

}
