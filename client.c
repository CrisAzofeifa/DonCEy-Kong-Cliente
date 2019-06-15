//
// Created by Roger Valderrama on 2019-06-14.
//

#include "client.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#define PORT 8080

// Base code from https://www.geeksforgeeks.org/socket-programming-cc/
// Original Author Akshat Sinha
// Modified Cristhofer

int sock = 0, valread;
struct sockaddr_in serv_addr;
char *hello = "Hello from client";
char buffer2[1024] ;

/**
 * This listens to the server continuously
 */
void listener() {
  memset(buffer2, 0, 1024);
  valread = read(sock, buffer2, 1024);
  printf("Here found the socket \n");
  printf(buffer2);

  // Here loads everything for first time

  while (1) {
    memset(buffer2, 0, 1024);
    valread = read(sock, buffer2, 1024);

    // Here allows everything to start moving

    if (valread == 0) {
      connectSocket();
      break;
    }
  }
}

/**
 * This connects the socket
 * @return
 */
void *connectSocket() {
  printf("connectSocket");

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }
  while (1) {
    memset(buffer2,0,1024)    ;
    valread = read( sock , buffer2, 1024);
    setvbuf(stdout,NULL,_IONBF,0);
    char* variable = buffer2;
    printf(buffer2);
    if (!stringEquals("main", buffer2)) {

      printf("I AM THE MAIN");
    }
    if (!stringEquals("listener", buffer2)) {
      listener();
      return ;
    }
    if (!stringEquals("get", buffer2)) {
      char *stuff = "prueba";

      valread = send(sock, stuff, strlen(stuff), 0);

    }
    else{
    }
  }
}

/**
 * Compare two strings
 * @param s string
 * @param p string
 * @return 0 if they are the same, 1 if does not.
 */
int stringEquals(char *s, char *p) {
  int i = 0;
  while (1) {
    if (p[i] == '\0' && s[i] == '\0') {
      return 0;
    }
    if (p[i] != s[i]) {
      return 1;
    }
    if (p[i] == '\0') {
      return 1;
    }
    if (s[i] == '\0') {
      return 1;
    }
    i++;
  }
}
