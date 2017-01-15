#include "platform.h"
#include "stream_tcp.h"
#include "stream_log.h"

int main(int argc, char* argv[]) {
	int sock = 0;
	if(argc < 2) {
		printf("%s port\n", argv[0]);
		return 1;
	}

	socketInit();
	sock = tcp_listen(atoi(argv[1])); 
	while(1) {
		size_t ret = 0;
		uint8_t buff[1024];
		stream_t* s = tcp_accept(sock);
	
		s = stream_log_create(s, "server.log");
		while((ret = stream_read(s, buff, sizeof(buff))) > 0) {
			printf("%s", buff);
			stream_write(s, buff, ret);
		}

		stream_close(s);
	}
	closeSocket(sock);
	socketDeinit();

	return 0;
}
