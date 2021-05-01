#ifndef HTTP_GET_H
#define HTTP_GET_H

struct http_get_response
{
    char* data;
    int hsize;
    int size;
};
typedef struct http_get_response http_get_response_t;

void http_get_free(http_get_response_t *);
http_get_response_t* http_get(const char* url);

#endif // HTTP_GET_H
