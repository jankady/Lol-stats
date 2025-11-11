#include <stdio.h>
#include "header/stats.h"
#include "header/utility.h"


int main(int argc, char **argv) {
    // check number of arguments
    if (argc != 4)
    {
        print_error(0,"",0);
        return 1;
    }
    // pridate treti argument jako test
    if (!validate_argument(argv[1]) && !validate_argument(argv[2]) && !validate_argument(argv[3])) {
        // stars the main program
        start_stats(argv[1], argv[2], argv[3]);
        return 0;

    }
    return 1;
}