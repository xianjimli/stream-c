#ifndef OSTREAM_H
#define OSTREAM_H

#include "types_def.h"

BEGIN_C_DECLS

struct _ostream_t;
typedef struct _ostream_t ostream_t;

typedef const char* (*ostream_get_name_t)(ostream_t* s);
typedef size_t (*ostream_write_t)(ostream_t* s, void* buff, size_t len);
typedef void   (*ostream_flush_t)(ostream_t* s);
typedef void   (*ostream_close_t)(ostream_t* s);

struct _ostream_t {
	ostream_write_t     write;
	ostream_flush_t     flush;
	ostream_get_name_t  get_name;
	ostream_close_t     close;
};

static inline size_t ostream_write(ostream_t* s, void* buff, size_t len) {
	return_value_if_fail(s != NULL && s->write != NULL && buff != NULL, 0);
	return s->write(s, buff, len);
}

static inline size_t ostream_write_c(ostream_t* s, uint8_t c) {
	return_value_if_fail(s != NULL && s->write != NULL, 0);
	return ostream_write(s, &c, 1);
}

static inline const char* ostream_get_name(ostream_t* s) {
	return_value_if_fail(s != NULL && s->get_name != NULL, NULL);
	return s->get_name(s);
}

static inline void   ostream_flush(ostream_t* s) {
	return_if_fail(s != NULL && s->flush != NULL);
	s->flush(s);
}

static inline void   ostream_close(ostream_t* s) {
	return_if_fail(s != NULL && s->close != NULL);
	s->close(s);
}

END_C_DECLS

#endif//OSTREAM_H

