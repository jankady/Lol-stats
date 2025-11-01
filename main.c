#include <stdio.h>
#include "header/stats.h"
#include "header/utility.h"


int main(int argc, char **argv) {

    // pridate treti argument jako test
    if (!validate_argument(argv[1]) && !validate_argument(argv[2])) {
        // stars the main program
        start_stats(argv[1], argv[2], "test");
        return 0;

    }
    return 1;
}