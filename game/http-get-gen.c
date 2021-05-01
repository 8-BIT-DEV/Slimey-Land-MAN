#include <stdio.h>
#include <stdlib.h>
#include <http-get-gen.h>
#include <matoya.h>

extern bool exitnow;

void http_get_free(http_get_response_t* res)
{
    MTY_Free(res->data);
    free(res);
}

http_get_response_t* http_get(const char* url)
{
    char host[256];
    char path[256];
    MTY_HttpParseUrl(url, host, 256, path, 256);
    http_get_response_t* res = malloc(sizeof(http_get_response_t));
    //res->size = httpGET(host, 80, path, &res->data);
    int stat = 0;
    bool err = MTY_HttpRequest(host, 80, false, "GET", path, "", "", 0, 5000, &res->data, &res->size, &stat);
    //res->hsize = getHeaderLength(res->data) + 4;
    //res->data = res->data + res->hsize;
    if(stat != 200)
    {
        printf("ERR:%s\n", MTY_GetLog());
        exitnow = true;
    }
    return res;
}
