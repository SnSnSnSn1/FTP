#include "url_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_url(char* buffer) {
    char* get = strstr(buffer, "GET ");
    if (get == NULL) {
        return NULL;
    }

    get += 4;  // 移动指针到 URL 开始的位置

    char* end = strchr(get, ' ');
    if (end == NULL) {
        end = strchr(get, '\r');
    }

    if (end == NULL) {
        return NULL;
    }

    size_t len = end - get;
    char* path = (char*)malloc(len + 1);
    if (path == NULL) {
        return NULL;
    }
    strncpy(path, get, len);
    path[len] = '\0';

    // 查找 URL 中的 '?' 字符，如果存在，则截断它
    char* query_pos = strchr(path, '?');
    if (query_pos != NULL) {
        *query_pos = '\0';
    }

    // 如果没有文件扩展名，则添加 ".html"
    if (strchr(path, '.') == NULL) {
        char* new_path = (char*)malloc(strlen(path) + 5);
        if (new_path == NULL) {
            free(path);
            return NULL;
        }
        strcpy(new_path, path);
        strcat(new_path, ".html");
        free(path);
        path = new_path;
    }

    return path;
}
