#ifndef ISTREAM_H
#define ISTREAM_H

#include "types_def.h"

BEGIN_C_DECLS

struct _istream_t;
typedef struct _istream_t istream_t;

typedef size_t    (*istream_read_t)(istream_t* s, void* buff, size_t len);
typedef bool_t (*istream_skip_t)(istream_t* s, int offset);
typedef bool_t (*istream_reset_t)(istream_t* s);
typedef void   (*istream_close_t)(istream_t* s);
typedef size_t (*istream_available_t)(istream_t* s);
typedef const char* (*istream_get_name_t)(istream_t* s);

struct _istream_t {
	istream_read_t      read;
	istream_skip_t      skip;
	istream_reset_t     reset;
	istream_available_t available;
	istream_get_name_t  get_name;
	istream_close_t     close;
};

static inline size_t istream_read(istream_t* s, void* buff, size_t len) {
	return_value_if_fail(s != NULL && s->read != NULL && buff != NULL, 0);
	return s->read(s, buff, len);
}

static inline bool_t istream_skip(istream_t* s, int offset) {
	return_value_if_fail(s != NULL && s->skip != NULL, 0);
	return s->skip(s, offset);
}

static inline size_t istream_available(istream_t* s) {
	return_value_if_fail(s != NULL && s->available != NULL, 0);
	
	return s->available(s);
}

static inline bool_t istream_reset(istream_t* s) {
	return_value_if_fail(s != NULL && s->reset != NULL, FALSE);

	return s->reset(s);
}

static inline const char* istream_get_name(istream_t* s) {
	return_value_if_fail(s != NULL && s->get_name != NULL, NULL);
	
	return s->get_name(s);
}

static inline void   istream_close(istream_t* s) {
	return_if_fail(s != NULL && s->close != NULL);
	s->close(s);
}

END_C_DECLS

#endif//ISTREAM_H

