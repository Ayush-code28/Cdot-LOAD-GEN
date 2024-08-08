
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void handle_sipp(void *arg, char *buffer) {
    int socket = *(int *)arg;
     // Free the allocated memory for the argument

    int bytesRead;

    printf("Client connected.\n");

    // Initial buffer processing
    printf("Received: in volte file  %s\n", buffer);


    // Extracting data from the buffer sent by main.c
    char source_ip[INET_ADDRSTRLEN], dest_ip[INET_ADDRSTRLEN];
    int source_port, dest_port, max_call, para_call;

    // Assuming the buffer format is: numericValue,sourceIp:sourcePort;destIp:destPort;maxCall
char *data = strchr(buffer, ',') + 1; // Skip the numericValue part
sscanf(data, "%[^;];%[^:]:%d;%d;%d", source_ip, dest_ip, &dest_port, &max_call, &para_call);


    printf("this is data variable in volte file%s\n", data);

    char srcip[BUFFER_SIZE];
    snprintf(srcip, BUFFER_SIZE, "%s:%d", source_ip, source_port);
    char destip[BUFFER_SIZE];
    snprintf(destip, BUFFER_SIZE, "%s:%d", dest_ip, dest_port);
    printf("Stored: source data: %s\n", srcip);
    printf("Stored: destination data: %s\n", destip);
    printf("Stored: max_call: %d\n", max_call);
    printf("para call: %d\n", para_call);
    const char *response = "Data received";
    write(socket, response, strlen(response));



   char *path="../test/SIPP_LOADGEN/sipp-1.1rc6_load_set/isfBest1";



    char run_script[BUFFER_SIZE];
    snprintf(run_script, BUFFER_SIZE, "../test/SIPP_LOADGEN/sipp-1.1rc6_load_set/sipp_2g_34_rtp %s:5040 -sn uac_pcap -i %s -p %d -mp 4000 -inf %s -r 60 -d 2 -nr -m %d -l %d -trace_msg -trace_err -trace_stat &",source_ip, dest_ip, dest_port,path, max_call, para_call);



    printf("The given Script is: %s\n", run_script);

    printf("Executing command: %s\n", run_script);

int  ret= system(run_script);
         if (ret == -1) {
        perror("system");

    }

    if (WIFEXITED(ret) && WEXITSTATUS(ret) == 0) {
        printf("script sipp Script ran successfully.\n");
    } else {
        printf("script sipp Script failed to run.\n");
    }

    free(buffer);


    close(socket);
}
