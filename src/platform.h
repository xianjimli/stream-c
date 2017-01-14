#include "types_def.h"

#ifndef PLATFORM_H
#define PLATFORM_H

BEGIN_C_DECLS

void socketInit();
void socketDeinit();
void msleep(int ms);
void closeSocket(int sock);

END_C_DECLS

#endif//PLATFORM_H
