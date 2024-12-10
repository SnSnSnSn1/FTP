#include "http_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "url_parser.h"  

#define BUFFER_SIZE 1024
#define LISTEN_PORT 8080

int sockfd;

void http_server_init(uint16_t port) {
    struct sockaddr_in address;
    int opt = 1;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(sockfd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", port);
}

void http_server_run() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    //char buffer[BUFFER_SIZE];

    while (1) {
        int client_socket = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        // Handle the request
        handle_request(client_socket);

        // Close the client socket
        close(client_socket);
    }
}

// 在 http_server.c 或相关的头文件中
void send_404(int client_socket) {
    const char* not_found = "HTTP/1.1 404 Not Found\r\n\r\n";
    send(client_socket, not_found, strlen(not_found), 0);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    printf("Client request: %s\n", buffer);

    // 简单的GET请求处理
    if (strstr(buffer, "GET")) {
        char *filename = parse_url(buffer);
        if (filename != NULL) {
            char filepath[256];
            if (strlen(filename) == 0) {
                sprintf(filepath, "public/index.html");
            } else {
                // 确保不会发生目录遍历攻击
                char *sanitized_path = strdup(filename); // 使用 strdup 来复制 filename
                char *last_slash = strrchr(sanitized_path, '/');
                if (last_slash != NULL && last_slash != sanitized_path) {
                    *last_slash = '\0'; // 去除路径中的最后一个 '/'
                }
                if (strstr(sanitized_path, "../") != NULL) {
                    send_404(client_socket);
                    free(sanitized_path);
                    free(filename);
                    close(client_socket);
                    return;
                }
                sprintf(filepath, "public%s", sanitized_path);
                free(sanitized_path);
            }

            int fd = open(filepath, O_RDONLY);
            if (fd != -1) {
                char http_header[256];
                sprintf(http_header, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", get_content_type(filename));
                send(client_socket, http_header, strlen(http_header), 0);

                char read_buffer[1024];
                int read_bytes;
                while ((read_bytes = read(fd, read_buffer, sizeof(read_buffer))) > 0) {
                    send(client_socket, read_buffer, read_bytes, 0);
                }
                close(fd);
            } else {
                send_404(client_socket);
            }
            free(filename);
        }
    }
    close(client_socket); // 确保在函数结束时关闭客户端套接字
}

char* get_content_type(char* filename) {
    // 简单的文件类型判断
    if (strstr(filename, ".html")) {
        return "text/html";
    } else if (strstr(filename, ".css")) {
        return "text/css";
    } else if (strstr(filename, ".js")) {
        return "application/javascript";
    } else if (strstr(filename, ".png")) {
        return "image/png";
    } else if (strstr(filename, ".jpg")) {
        return "image/jpeg";
    } else {
        return "text/plain";
    }
}
