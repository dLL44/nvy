#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool PRIVILEGED = false;
bool TEMP = false;
#define CONTAINER

void createcont(const char* image, bool isPrivileged, bool isTemp)
{
    char command[256]; // Increased buffer size to accommodate longer commands
    char containerID[64];
    char rsvp[10];
    FILE* fp;

    if (isPrivileged) {
        snprintf(command, sizeof(command), "docker create -it --privileged %s", image);
    } else {
        snprintf(command, sizeof(command), "docker create -it %s", image);
    }

    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to execute command\n");
        return;
    }

    if (fgets(containerID, sizeof(containerID), fp) != NULL) {
        printf("Container created successfully with ID: %s", containerID);
        
        if (isTemp) {
            // Get the value of the %PROGRAMFILES% environment variable
            char* programFilesPath = getenv("PROGRAMFILES");
            if (programFilesPath == NULL) {
                fprintf(stderr, "Failed to get PROGRAMFILES environment variable\n");
                return;
            }

            // Construct the command to copy the README file
            snprintf(command, sizeof(command), "docker cp \"%s\\nvy\\README\" %s:/README", programFilesPath, containerID);
            int result = system(command);
            if (result != 0) {
                fprintf(stderr, "Failed to copy README file into container\n");
                // Additional error handling if necessary
                return;
            }

            // Automatically enter the container if it's temporary
            snprintf(command, sizeof(command), "docker start %s", containerID);
            system(command);
            snprintf(command, sizeof(command), "docker exec -it %s bash", containerID);
            system(command);
            
            // Cleanup after exiting the container
            snprintf(command, sizeof(command), "docker stop %s", containerID);
            system(command);
            snprintf(command, sizeof(command), "docker rm %s", containerID);
            system(command);
        } else {
            printf("\nWould you like to run your container? [y/N] ");
            if (scanf("%9s", rsvp) != 1) { // Validate input
                fprintf(stderr, "Invalid input\n");
                pclose(fp);
                return;
            }
            if (strcmp(rsvp, "y") == 0) {
                snprintf(command, sizeof(command), "docker start %s", containerID);
                system(command);
                snprintf(command, sizeof(command), "docker exec -it %s bash", containerID);
                system(command);
            } else {
                printf("Exiting without running the container.\n");
            }
        }
    } else {
        fprintf(stderr, "Failed to read container ID\n");
    }
}

void delcont(const char containerID[64], bool isTemp)
{
    char command[100];
    char rsvp[10];
    
    if (!isTemp) {
        printf("Are you sure? This will delete all data and files in the container. [y/N] ");
        if (scanf("%9s", rsvp) != 1) { // Validate input
            fprintf(stderr, "Invalid input\n");
            return;
        }
        if (strcmp(rsvp, "y") != 0) {
            printf("Canceled\n");
            return;
        }
    }   
    snprintf(command, sizeof(command), "docker stop %s", containerID);
    system(command);
    printf(" stopped");
    snprintf(command, sizeof(command), "docker rm %s", containerID);
    system(command);
    printf(" deleted");
}
