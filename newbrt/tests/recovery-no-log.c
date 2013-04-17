#ident "$Id$"
// test recovery with no log

#include "test.h"
#include "includes.h"

#define TESTDIR __FILE__ ".dir"

static int 
run_test(void) {
    int r;

    // setup the test dir
    r = system("rm -rf " TESTDIR);
    CKERR(r);
    r = toku_os_mkdir(TESTDIR, S_IRWXU); assert(r == 0);

    // redirect stderr
    int devnul = open(DEV_NULL_FILE, O_WRONLY);
    assert(devnul>=0);
    r = toku_dup2(devnul, fileno(stderr)); 	    assert(r==fileno(stderr));
    r = close(devnul);                      assert(r==0);

    // run recovery
    r = tokudb_recover(NULL,
		       NULL_keep_zombie_callback,
		       NULL_prepared_txn_callback,
		       NULL_keep_cachetable_callback,
		       NULL_setup_db_callback,
		       NULL_close_db_callback,
		       NULL_logger, TESTDIR, TESTDIR, 0, 0, 0, NULL, 0); 
    assert(r != 0);

    r = system("rm -rf " TESTDIR);
    CKERR(r);

    return 0;
}

int
test_main(int UU(argc), const char *UU(argv[])) {
    int r;
    r = run_test();
    return r;
}
