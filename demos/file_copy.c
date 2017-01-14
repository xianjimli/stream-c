#include "istream_file.h"
#include "ostream_file.h"

int main(int argc, char* argv[]) {	
	uint8_t buff[1024];
	istream_t* in = NULL;
	ostream_t* out = NULL;

	if(argc < 3) {
		printf("Usage: %s srcfile dstfile\n", argv[0]);
		return 1;
	}
	
	in = istream_file_create(argv[1]);
	out = ostream_file_create(argv[2]);
	if(in && out) {
		size_t finish_size = 0;
		size_t total_size = istream_available(in); 
		while(1) {
			size_t ret = istream_read(in, buff, sizeof(buff));
			if(ret > 0) {
				finish_size += ret;
				printf("ret=%zu %zu/%zu\n", ret, finish_size, total_size);
				ostream_write(out, buff, ret);
			}else{
				break;
			}
		}
	}

	istream_close(in);
	ostream_close(out);

	return 0;
}
