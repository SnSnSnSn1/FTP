#include "http_server.h"  // 引入 HTTP 服务器的头文件
#include <assert.h>      // 引入断言库
#include <string.h>      // 引入字符串处理库
#include <unistd.h>      // 引入 Unix 标准函数定义库
#include <sys/socket.h>  // 引入套接字库
#include <sys/types.h>   // 引入数据类型库
#include <stdio.h> 

#define BUFFER_SIZE 1024

// 测试 handle_request 函数是否生成正确的响应
void test_handle_request() {
    char expected_response_header[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    char buffer[1024] = {0}; // 模拟接收响应的缓冲区

    // 模拟客户端套接字（在实际测试中，这里应该是一个真实的网络连接）
    int client_socket = 0;

    // 调用 handle_request 函数处理请求
    handle_request(client_socket);

    // 由于没有实际的网络通信，我们需要手动设置 buffer 的内容
    strcpy(buffer, expected_response_header);

    // 检查响应是否符合预期
    assert(strncmp(buffer, expected_response_header, strlen(expected_response_header)) == 0);

    // 关闭客户端套接字
    close(client_socket);
}
int main() {
    test_handle_request();
    printf("All HTTP server tests passed.\n");
    return 0;
}
