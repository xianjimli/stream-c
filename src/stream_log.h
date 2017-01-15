#include "stream.h"

#ifndef STREAM_LOG_H
#define STREAM_LOG_H

BEGIN_C_DECLS

stream_t* stream_log_create(stream_t* org_stream, const char* filename);

END_C_DECLS

#endif//STREAM_LOG_H
