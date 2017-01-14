
#include "ostream_file.h"

typedef struct _ostream_file_t {
	ostream_t stream;
	char* filename;
	FILE* fp;
}ostream_file_t;

static size_t ostream_file_write(ostream_t* s, void* buff, size_t len) {		
	ostream_file_t* ofs = (ostream_file_t*)s;

	return fwrite(buff, 1, len, ofs->fp);
}

static void   ostream_file_flush(ostream_t* s) {
	ostream_file_t* ofs = (ostream_file_t*)s;
	
	fflush(ofs->fp);
}

static void   ostream_file_close(ostream_t* s) {
	ostream_file_t* ofs = (ostream_file_t*)s;
	if(ofs->fp) {
		free(ofs->filename);
		fclose(ofs->fp);
		memset(ofs, 0x00, sizeof(ostream_file_t));
		free(ofs);
	}
}

static const  char* ostream_file_get_name(ostream_t* s) {
	ostream_file_t* ofs = (ostream_file_t*)s;
	
	return ofs->filename;
}

ostream_t* ostream_file_create(const char* filename) {
	FILE* fp = NULL;
	ostream_file_t* ofs = NULL;
	return_value_if_fail(filename != NULL, NULL);

	fp = fopen(filename, "w+b");
	return_value_if_fail(fp != NULL, NULL);
	
	ofs = (ostream_file_t*)calloc(1, sizeof(ostream_file_t));
	if(ofs) {	
		ofs->fp = fp;
		ofs->filename = strdup(filename);
		ofs->stream.write     = ostream_file_write;
		ofs->stream.flush     = ostream_file_flush;
		ofs->stream.close     = ostream_file_close;
		ofs->stream.get_name  = ostream_file_get_name;
	}else{
		fclose(fp);
	}

	return &(ofs->stream);
}
