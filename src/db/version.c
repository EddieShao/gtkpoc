#include <sqlite3.h>

#include "db/version.h"

const char *gtkpoc_sqlite_version() {
    return sqlite3_libversion();
}
