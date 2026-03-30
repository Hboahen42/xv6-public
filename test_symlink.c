#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void
test_basic(void) {
    int fd, n;
    char buf[32];
    struct stat st;

    // create the target file
    fd = open("basic_target", O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf(1, "FAIL basic: could not create target\n");
        exit();
    }
    write(fd, "hello", 5);
    close(fd);

    // create the symlink
    if (symlink("basic_target", "basic_link") < 0) {
        printf(1, "FAIL basic: could not create symlink\n");
        exit();
    }

    // open through the symlink, read contents
    fd = open("basic_link", O_RDONLY);
    if (fd < 0) {
        printf(1, "FAIL basic: could not open through symlink\n");
        exit();
    }
    n = read(fd, buf, sizeof(buf));
    close(fd);
    if (n != 5 || buf[0] != 'h') {
        printf(1, "FAIL basic: wrong content read through symlink\n");
        exit();
    }

    // open with O_FOLLOW: should get the symlink inode, not the target
    fd = open("basic_link", O_RDONLY | O_NOFOLLOW);
    if (fd < 0) {
        printf(1, "FAIL basic: could not open with O_FOLLOW\n");
        exit();
    }
    fstat(fd, &st);
    close(fd);
    if (st.type != T_SYMLINK) {
        printf(1, "FAIL basic: O_NOFOLLOW gave the wrong type %d\n", st.type);
        exit();
    }

    // confirm symlink's stored size equals length of "basic_target"
    if (st.size != 12) {
        printf(1, "FAIL basic: symlink's stored size is %d, should be 12\n", st.size);
        exit();
    }

    printf(1, "basic: ok\n");
}

// void test_chain(void);
// void test_dangling(void);
// void test_cycle(void);

int
main(void) {
    test_basic();
    //test_chain();
    //test_dangling();
    //test_cycle();
    printf(1, "All tests passed!\n");
    exit();
}
