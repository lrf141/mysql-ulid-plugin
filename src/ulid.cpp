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
    // TODO: return human readable string.
    // NOW-ex: 0x303030314A414E474A4E4D434D46303752303030303030303030
    return result;
}
