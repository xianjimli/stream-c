#include "platform.h"

#include <sys/types.h>

#include <stdio.h>
#include "stream_log.h"

typedef struct _stream_log_t {
	stream_t stream;
	FILE* fp;
	stream_t* org_stream;
}stream_log_t;

static void log_buff(FILE* fp, const char* prefix, void* buff, size_t len) {
	uint8_t* p = buff;
	fprintf(fp, "%s", prefix);
	for(size_t i = 0; i < len; i++) {
		int ch = p[i];
		if(ch == '\n' || ch == '\r') {
			fprintf(fp, "LF ");
		}else{
			fprintf(fp, "%02x(%c) ", ch, ch);
		}
		if(i > 10) {
			fprintf(fp, " ...");
			break;
		}
	}
	fprintf(fp, "\n");
}

static int stream_log_read(stream_t* s, void* buff, size_t len) {
	stream_log_t* log = (stream_log_t*)s;
	int ret = stream_read(log->org_stream, buff, len);
	if(ret > 0) {
		log_buff(log->fp, ">:", buff, ret);
	}

	return ret;
}

static int stream_log_write(stream_t* s, void* buff, size_t len) {
	stream_log_t* log = (stream_log_t*)s;
	log_buff(log->fp, "<:", buff, len);
	return stream_write(log->org_stream, buff, len);
}

static void   stream_log_close(stream_t* s) {
	stream_log_t* log = (stream_log_t*)s;
	stream_close(log->org_stream);
	fclose(log->fp);
	memset(log, 0x00, sizeof(stream_log_t));
	free(log);
}

static void   stream_log_flush(stream_t* s) {
	stream_log_t* log = (stream_log_t*)s;
	stream_flush(log->org_stream);
	fflush(log->fp);

	return;
}

stream_t* stream_log_create(stream_t* org_stream, const char* filename) {
	return_value_if_fail(org_stream != NULL && filename != NULL, NULL);

	stream_log_t* log = (stream_log_t*)calloc(1, sizeof(stream_log_t));
	if(log) {
		log->org_stream = org_stream;
		log->fp = fopen(filename, "w+b");
		log->stream.read = stream_log_read;
		log->stream.write = stream_log_write;
		log->stream.flush = stream_log_flush;
		log->stream.close = stream_log_close;
	}

	return (stream_t*)log;
}

