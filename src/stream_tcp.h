#ifndef STREAM_TCP_H
#define STREAM_TCP_H

#include "stream.h"

BEGIN_C_DECLS

int       tcp_listen(int port);
stream_t* tcp_connect(const char* host, int port);
stream_t* tcp_accept(int sock);

END_C_DECLS

#endif//STREAM_TCP_H

