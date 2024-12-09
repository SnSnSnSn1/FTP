#include "url_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Parse the URL from the HTTP request buffer and return the file path.
 * @param buffer The HTTP request buffer.
 * @return The file path or NULL if the URL is invalid.
 */
char* parse_url(char* buffer) {
    // Find the "GET " keyword and extract the URL path
    char* get = strstr(buffer, "GET ");
    if (get == NULL) {
        return NULL;
    }

    // Move the pointer to the start of the URL path
    get += 4;

    // Find the end of the URL path (space or HTTP version)
    char* end = strchr(get, ' ');
    if (end == NULL) {
        end = strchr(get, '\r');
    }

    if (end == NULL) {
        return NULL;
    }

    // Calculate the length of the URL path
    size_t len = end - get;

    // Allocate memory for the file path and copy the URL path
    char* path = (char*)malloc(len + 1);
    if (path == NULL) {
        return NULL;
    }
    strncpy(path, get, len);
    path[len] = '\0';

    // Append ".html" if no file extension is provided
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
