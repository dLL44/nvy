#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nvyfuctions.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: nvy <option> <container> <optional flags>\n");
        return 1; // Return error code
    }
    
    char* action = argv[1];
    char* cName  = argv[2];

    if (strcmp(action, "help") == 0 && cName == NULL){
        printf(" ███▄    █ ██▒   █▓▓██   ██▓\n ██ ▀█   █▓██░   █▒ ▒██  ██▒\n▓██  ▀█ ██▒▓██  █▒░  ▒██ ██░\n▓██▒  ▐▌██▒ ▒██ █░░  ░ ▐██▓░\n▒██░   ▓██░  ▒▀█░    ░ ██▒▓░\n░ ▒░   ▒ ▒   ░ ▐░     ██▒▒▒ \n░ ░░   ░ ▒░  ░ ░░   ▓██ ░▒░ \n   ░   ░ ░     ░░   ▒ ▒ ░░  \n         ░      ░   ░ ░     \n               ░    ░ ░ \n~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n\n  disposable VMs reimagined\n\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n\ncreated by @dLL44 on tha github ya herd?\nUsage: nvy <option> <container> <optional flags>\n\n    -p, --privileged \n        Runs the container on a higher status\n    -t, --temporary\n        Runs a temporary (disposable) container\n    help\n        This page\n    create\n        create a docker container ( paired with both -t and -p flags )\n    del\n        delete an existing container by id\n----------------------------\n\nIssue? Let me know. \nukw2fm\n\n----------------------------");
    } else {
        printf("Usage: nvy <option> <container> <optional flags>\n");
    }

    // Iterate through command-line arguments to detect flags
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--privileged") == 0) {
            PRIVILEGED = true; // Set the privileged flag if --privileged is provided
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--temporary") == 0){
            TEMP = true;
        } else {
            printf("Unknown flag: %s\n", argv[i]);
            return 1; // Return error code
        }
    }

    if (strcmp(action, "create") == 0) {
        // Call createcont function with appropriate arguments
        createcont(cName, PRIVILEGED, TEMP);
    } else if (strcmp(action, "del") == 0) {
        delcont(cName, TEMP);
    } else if (strcmp(action, "help") == 0) {
        printf("\n     ***** *     **                       ***** *    **   \n  ******  **    **** *                 ******  *  *****   \n **   *  * **    ****  **             **   *  *     ***** \n*    *  *  **    * *   **            *    *  **     * **  \n    *  *    **   *      **    ***        *  ***     *     \n   ** **    **   *       **    ***      **   **     *     \n   ** **     **  *       **     ***     **   **     *     \n   ** **     **  *       **      **     **   **     *     \n   ** **      ** *       **      **     **   **     *     \n   ** **      ** *       **      **     **   **     *     \n   *  **       ***       **      **      **  **     *     \n      *        ***       **      *        ** *      *     \n  ****          **        *******          ***      *     \n *  *****                  *****            *********     \n*     **                                      **** ***    \n*                                                   ***   \n **                                     ********     ***  \n                                      *************  **   \n                                     *           ****     \n\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n  disposable VMs reimagined\n\n~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\ncreated by @dLL44 on tha github ya herd?\nUsage: nvy <option> <container> <optional flags>\n\n    -p, --privileged \n        Runs the container on a higher status\n    -t, --temporary\n        Runs a temporary (disposable) container\n    help\n        This page\n    create\n        create a docker container ( paired with both -t and -p flags. P.S it work like this: nvy create ubuntu [flags] )\n    del\n        delete an existing container by id\n----------------------------\n\nIssue? Let me know. \nukw2fm\n\n----------------------------");
    } else {
        printf("Unknown option: %s\n", action);
        return 1; // Return error code
    }
    
    return 0;
}
