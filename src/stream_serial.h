#ifndef STREAM_SERIAL_H
#define STREAM_SERIAL_H
#include "stream.h"

BEGIN_C_DECLS

stream_t* stream_serial_create(
		const char* port,
		uint32_t baudrate,
		int bytesize,   /*options:5,6,7,8*/
		int parity,     /*0:none, 1:odd, 2:even*/
		int stopbits,   /*options, 1, 2*/
		int flowcontrol /*0:none, 1:software, 2:hardware*/
	);

END_C_DECLS

#endif//STREAM_SERIAL_H

