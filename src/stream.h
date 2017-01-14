#ifndef STREAM_H
#define STREAM_H

#include "types_def.h"

BEGIN_C_DECLS

struct _stream_t;
typedef struct _stream_t stream_t;

typedef int    (*stream_read_t)(stream_t* s, void* buff, size_t len);
typedef int    (*stream_write_t)(stream_t* s, void* buff, size_t len);
typedef void   (*stream_flush_t)(stream_t* s);
typedef void   (*stream_close_t)(stream_t* s);

struct _stream_t {
	stream_read_t  read;
	stream_write_t write;
	stream_flush_t flush;
	stream_close_t close;
};

static inline int stream_read(stream_t* s, void* buff, size_t len) {
	return_value_if_fail(s != NULL && s->read != NULL && buff != NULL, 0);
	return s->read(s, buff, len);
}

static inline int stream_write(stream_t* s, void* buff, size_t len) {
	return_value_if_fail(s != NULL && s->write != NULL && buff != NULL, 0);
	return s->write(s, buff, len);
}

static inline int stream_read_c(stream_t* s) {
	uint8_t c = 0;
	return_value_if_fail(s != NULL && s->read != NULL, -1);
	
	return stream_read(s, &c, 1) == 1 ? c : -1;
}

static inline int stream_write_c(stream_t* s, uint8_t c) {
	return_value_if_fail(s != NULL && s->write != NULL, 0);

	return stream_write(s, &c, 1);
}

static inline void   stream_flush(stream_t* s) {
	return_if_fail(s != NULL && s->flush != NULL);
	s->flush(s);
}

static inline void   stream_close(stream_t* s) {
	return_if_fail(s != NULL && s->close != NULL);
	s->close(s);
}

END_C_DECLS

#endif//STREAM_H

