#include "url_parser.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void test_parse_url() {
    char request[] = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url = parse_url(request);
    assert(strcmp(url, "/index.html") == 0);
    free(url);
}

void test_parse_url_without_extension() {
    char request[] = "GET /path/to/file HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url = parse_url(request);
    assert(strcmp(url, "/path/to/file.html") == 0);
    free(url);
}

void test_parse_url_with_query() {
    char request[] = "GET /search?q=example HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url = parse_url(request);
    assert(strcmp(url, "/search.html") == 0); // 确保这里与 parse_url 函数的实现一致
    free(url);
}

void test_parse_url_invalid() {
    char request[] = "INVALID /request";
    char *url = parse_url(request);
    assert(url == NULL);
}

int main() {
    test_parse_url();
    test_parse_url_without_extension();
    test_parse_url_with_query();
    test_parse_url_invalid();
    printf("All URL parser tests passed.\n");
    return 0;
}
