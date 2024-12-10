#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <stdint.h> 
void http_server_init(uint16_t port);
void http_server_run();
void handle_request(int client_socket);
char* get_content_type(char* filename);

#endif
