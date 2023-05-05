#include "includes.h"

int
main(int argc, char* argv[]) {
    uint32_t err = 0;

	err = CsUdsClientInitialize();
    BAIL_ON_CSUDS_ERROR(err);

cleanup:
    CsUdsClientFinalize();
    return err;
error:
    goto cleanup;
}

