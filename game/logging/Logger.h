#ifndef LOGGER_H
#define LOGGER_H

#define LOG(level, say) level(say)

void INFO(char* say);
void WARNING(char* say);
void ERROR(char* say);
void CRASH(char* say);

void DONE();

#endif // LOGGER_H
