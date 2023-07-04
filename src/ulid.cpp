#include <limits>
#include <mysql.h>
#include <cstring>

extern "C" bool ulid_init(UDF_INIT *, UDF_ARGS *, char *message) {
#ifndef __SIZEOF_INT128__
    return false;
#else
    // No support if it does not use uint128_t
    strcpy(message, "if not support __uint128_t, can not use ULID().");
    return true;
#endif
}

extern "C" void ulid_deinit(UDF_INIT *){}

extern "C" char *ulid(UDF_INIT *, UDF_ARGS *, char *result, unsigned long *length, char *is_null, char *error) {
    return nullptr;
}
