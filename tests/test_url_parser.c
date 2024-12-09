#include "url_parser.h"
#include <check.h>
#include <stdio.h>

// 测试 parse_url 函数
START_TEST(test_parse_url)
{
    // 测试有效的URL
    char request[] = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url = parse_url(request);
    ck_assert_str_eq(url, "/index.html");
    free(url);

    // 测试没有文件扩展名的URL
    char request2[] = "GET /path/to/file HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url2 = parse_url(request2);
    ck_assert_str_eq(url2, "/path/to/file.html");
    free(url2);

    // 测试带有查询参数的URL
    char request3[] = "GET /search?q=example HTTP/1.1\r\nHost: localhost\r\n\r\n";
    char *url3 = parse_url(request3);
    ck_assert_str_eq(url3, "/search.html");
    free(url3);
}
END_TEST

// 测试套件
Suite *url_parser_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("URL Parser");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_parse_url);
    suite_add_tcase(s, tc_core);

    return s;
}

// 测试运行器
int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = url_parser_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
