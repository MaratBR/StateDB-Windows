#pragma once

// DB features and settings
#define STATEDB_CHANGES_TRACING_MODE_ALWAYS		2	// Always notify clients about new value
#define STATEDB_CHANGES_TRACING_MODE_DEMAND		1	// Don't notify but support CACHE_CHECK_CMD
#define STATEDB_CHANGES_TRACING_MODE_DISABLED	0	// Don't notify and don't support CACHE_CHECK_CMD

#ifndef STATEDB_CHANGES_TRACING_MODE
#	define STATEDB_CHANGES_TRACING_MODE STATEDB_CHANGES_TRACING_MODE_ALWAYS
#endif

#ifndef STATEDB_CHANGES_INCLUDE_VALUE
#	define STATEDB_CHANGES_INCLUDE_VALUE false
#endif

#ifndef CHECK_UNIMPLEMENTED_CMD_CODES
#	define CHECK_UNIMPLEMENTED_CMD_CODES true
#endif

#ifndef IGNORE_MAJOR_VERSION_MISMATCH
#define IGNORE_MAJOR_VERSION_MISMATCH true
#endif


#ifndef STATEDB_NET_TRASH_BUF_SIZE
#	define STATEDB_NET_TRASH_BUF_SIZE 256 // The size of the buffer for discarding data from TCP socket (net_utils.h)
#endif

#ifndef STATEDB_BLOCK_SIZE
#	define STATEDB_BLOCK_SIZE 1024
#endif

#ifndef STATEDB_MAX_BLOCK_SIZE
#define STATEDB_MAX_BLOCK_SIZE (1024*1024*256)
#endif

#ifndef STATEDB_NET_PING_TIMEOUT
#define STATEDB_NET_PING_TIMEOUT ::boost::posix_time::milliseconds(15000)
#endif

#ifndef STATEDB_NET_HELLO_TIMEOUT
#define STATEDB_NET_HELLO_TIMEOUT  ::boost::posix_time::milliseconds(20000)
#endif

#ifndef STATEDB_MAX_FSTREAM_BUFFER_SIZE
#define STATEDB_MAX_FSTREAM_BUFFER_SIZE 1024*1024 // 1M buffer for inserting in the middle
#endif

#define STATEDB_INIT_CONTAINER_VAR(name, obj) ::statedb::segment_container<decltype(obj)> name(obj, STATEDB_BLOCK_SIZE)

#define STATEDB_ZEROES 0
#define STATEDB_ONES (~0)
#define STATEDB_EMPTY_SPACE_BYTE STATEDB_ZEROES
#define STATEDB_DEFAULT_DB_FILE _DD("storage-D.statedb", "storage.statedb")

#include "commands.h"

#define STATEDB_DB_INT16_TYPE 1
#define STATEDB_DB_BYTE_TYPE 2
#define STATEDB_DB_INT32_TYPE 3
#define STATEDB_DB_DYNAMIC 4

#define STATEDB_USER_DTYPE_LOW 256


