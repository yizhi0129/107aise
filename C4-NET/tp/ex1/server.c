#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

int safe_write(int fd, char *buff, size_t size) {
  size_t written = 0;

  while (0 < (size - written)) {
    ssize_t ret = write(fd, buff + written, size - written);

    if (ret < 0) {
      perror("write");
      return -1;
    }

    written += ret;
  }
  
  return 0;
}

void *handle_client(void *psocket) {
  int client_fd = *((int *)psocket);

  FILE *in = fopen("./secret.txt", "r");

  if (!in) {
    perror("fopen");
    return NULL;
  }

  char buff[1024];

  while (fgets(buff, 1024, in)) {
    if (safe_write(client_fd, buff, strlen(buff))) {
      close(client_fd);
      return NULL;
    }

    if (strstr(buff, "\033[H")) {
      usleep(41666);
    }
  }

  (void)fclose(in);
  close(client_fd);

  return NULL;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    (void)fprintf(stderr, "Usage %s [PORT]\n", argv[0]);
    exit(1);
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *aret = NULL;

  int ret = getaddrinfo(NULL, argv[1], &hints, &aret);

  if (ret < 0) {
    perror("getaddrinfo");
    return 1;
  }

  struct addrinfo *tmp = NULL;

  int sock = -1;
  int success = 0;

  for (tmp = aret; tmp != NULL; tmp = tmp->ai_next) {
    /* Parcours des choix*/
    sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);

    if (sock < 0) {
      continue;
    }

    if (bind(sock, tmp->ai_addr, tmp->ai_addrlen)) {
      continue;
    }

    if (listen(sock, 5)) {
      continue;
    }

    /* All OK */
    success = 1;
    break;
  }

  if (!success) {
    (void)fprintf(stderr, "Failed to create server");
    exit(1);
  }

  while (1) {
    struct sockaddr addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = accept(sock, &addr, &len);

    if (ret < 0) {
      perror("accept");
      exit(1);
    }

    /* We have a client */
    int *sockfd = malloc(sizeof(int));

    if (sockfd == NULL) {
      perror("malloc");
      continue;
    }

    *sockfd = ret;

    pthread_t th = 0;
    pthread_create(&th, NULL, handle_client, sockfd);
  }

  return 0;
}
