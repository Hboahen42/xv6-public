#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf(1, "Usage: mklink target path\n");
        exit();
    }
    if (symlink(argv[1], argv[2]) < 0) {
        printf(1, "%s failed to create\n", argv[2]);
        exit();
    }
    printf(1, "%s -> %s\n", argv[2], argv[1]);
    exit();
}