#include "platform.h"
#include "stream_tcp.h"

int main(int argc, char* argv[]) {
	stream_t* s = NULL;

	if(argc < 3) {
		printf("%s host port\n", argv[0]);
		return 1;
	}
	socketInit();
	s = tcp_connect(argv[1], atoi(argv[2]));
	if(s) {
		int i = 0;
		size_t ret = 0;
		char buff[1024];
		snprintf(buff, sizeof(buff), "start\n");

		while((ret = stream_write(s, buff, sizeof(buff))) > 0) {
			stream_read(s, buff, ret);
			printf("get: %s", buff);
			snprintf(buff, sizeof(buff), "packet %d\n", i);
			i++;
			msleep(500);
		}

		stream_close(s);
	}
	socketDeinit();
	
	return 0;
}
