#include <mysql.h>

extern "C" bool ulid_init(UDF_INIT *, UDF_ARGS *, char *) {
    return false;
}

extern "C" void ulid_deinit(UDF_INIT *){}

extern "C" char *ulid(UDF_INIT *, UDF_ARGS *, char *result, unsigned long *length, char *is_null, char *error) {
    return nullptr;
}
