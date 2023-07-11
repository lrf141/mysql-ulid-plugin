#include <ctime>
#include <mysql.h>
#include <mysql/udf_registration_types.h>
#include <cstring>
#include <mutex>
#include "ulid_generator.h"

extern "C" bool ulid_init(UDF_INIT *, UDF_ARGS *, char *) {
    return false;
}

extern "C" void ulid_deinit(UDF_INIT *){}

// if mysql client run with --binary-as-hex=1, return string is represent as hex
extern "C" char *ulid(UDF_INIT *, UDF_ARGS *, char *result, unsigned long *length, char *is_null, char *) {
    time_t now;
    ULID ulidGenerator;

    time(&now);

    std::string ulidString = ulidGenerator.Create(now);
    strcpy(result, ulidString.c_str());
    *length = strlen(result);

    return result;
}
