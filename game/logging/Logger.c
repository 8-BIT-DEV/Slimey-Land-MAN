#include <logging/Logger.h>

void INFO(char* say)
{
    printf("INFO - %s\n", say);
}

void WARNING(char* say)
{
    printf("WARNING - %s\n", say);
}

void ERROR(char* say)
{
    printf("ERROR - %s\n", say);
}

void CRASH(char* say)
{
    printf("CRASH - %s\n", say);
    exit(-1);
}
