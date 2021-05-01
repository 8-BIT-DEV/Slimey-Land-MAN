#include <stdio.h>
#include <stdlib.h>
#include <http-get-gen.h>
#include <http.h>
#include <matoya.h>

void http_get_free(http_get_response_t* res)
{
    free(res->data-res->hsize);
    free(res);
}

http_get_response_t* http_get(const char* url)
{
    char host[256];
    char path[256];
    MTY_HttpParseUrl(url, host, 256, path, 256);
    http_get_response_t* res = malloc(sizeof(http_get_response_t));
    res->size = httpGET(host, 80, path, &res->data);
    res->hsize = getHeaderLength(res->data) + 4;
    res->data = res->data + res->hsize;
    return res;
}
