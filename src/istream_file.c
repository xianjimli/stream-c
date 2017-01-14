#include "istream_file.h"
#include <sys/stat.h>
#include <stdio.h>

typedef struct _istream_file_t {
	istream_t stream;
	char* filename;
	FILE* fp;
	size_t size;
}istream_file_t;

static size_t istream_file_read(istream_t* s, void* buff, size_t len) {
	istream_file_t* ifs = (istream_file_t*)s;

	return fread(buff, 1, len, ifs->fp);
}

static bool_t istream_file_skip(istream_t* s, int offset) {
	istream_file_t* ifs = (istream_file_t*)s;
	
	return 0 == fseek(ifs->fp, offset, SEEK_CUR);
}

static bool_t istream_file_reset(istream_t* s) {
	istream_file_t* ifs = (istream_file_t*)s;
	
	return 0 == fseek(ifs->fp, 0, SEEK_SET);
}

static size_t istream_file_available(istream_t* s) {
	istream_file_t* ifs = (istream_file_t*)s;
	
	return ifs->size - ftell(ifs->fp);
}

static const char* istream_file_get_name(istream_t* s) {
	istream_file_t* ifs = (istream_file_t*)s;

	return ifs->filename;
}

static void   istream_file_close(istream_t* s) {
	istream_file_t* ifs = (istream_file_t*)s;

	if(ifs->fp) {
		fclose(ifs->fp);
		free(ifs->filename);
		memset(ifs, 0x00, sizeof(istream_file_t));
		free(ifs);
	}

	return;
}

istream_t* istream_file_create(const char* filename) {
	FILE* fp = NULL;
	struct stat st;
	istream_file_t* ifs = NULL;

	return_value_if_fail(filename != NULL, NULL);
	return_value_if_fail(0 == stat(filename, &st), NULL);

	fp = fopen(filename, "rb");
	return_value_if_fail(fp != NULL, NULL);
	
	ifs = (istream_file_t*)calloc(1, sizeof(istream_file_t));
	if(ifs) {	
		ifs->fp = fp;
		ifs->size = st.st_size;
		ifs->filename = strdup(filename);
		ifs->stream.read      = istream_file_read;
		ifs->stream.reset     = istream_file_reset;
		ifs->stream.available = istream_file_available;
		ifs->stream.skip      = istream_file_skip;
		ifs->stream.close     = istream_file_close;
		ifs->stream.get_name  = istream_file_get_name;
	}else{
		fclose(fp);
	}

	return &(ifs->stream);
}


