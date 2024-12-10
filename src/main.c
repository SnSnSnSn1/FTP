#include "http_server.h"

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    // 初始化服务器，设置监听端口等
    http_server_init(8080);

    // 运行服务器
    http_server_run();

    return 0;
}
