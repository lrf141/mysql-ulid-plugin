#include <mysql.h>

extern "C" bool ulid_init(UDF_INIT *, UDF_ARGS *, char *) {
  return false;
}

extern "C" void ulid_deinit(UDF_INIT *){}

extern "C" long long ulid(UDF_INIT *initid, UDF_ARGS *, char *, char *) {
  return 1;
}
