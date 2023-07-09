#include <ctime>
#include <mysql.h>
#include <mysql/udf_registration_types.h>
#include <cstring>
#include "ulid_generator.h"

extern "C" bool ulid_init(UDF_INIT *, UDF_ARGS *, char *) {
    return false;
}

extern "C" void ulid_deinit(UDF_INIT *){}

extern "C" char *ulid(UDF_INIT *, UDF_ARGS *, char *result, unsigned long *length, char *is_null, char *) {
    time_t now;
    ULID ulidGenerator;

    time(&now);
    // TODO: check randomness pattern
    std::string ulidString = ulidGenerator.Create(now);
    strcpy(result, ulidString.c_str());
    *length = strlen(result);
    // if mysql client run with --binary-as-hex=1, return string is represent as hex
    return result;
}
