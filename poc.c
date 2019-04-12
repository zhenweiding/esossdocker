#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/xattr.h>

#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/falloc.h>
#include <linux/loop.h>

static void activity(char *mpoint) {

  char *foo_bar_baz;
  int err;

  static int buf[8192];
  memset(buf, 0, sizeof(buf));

  err = asprintf(&foo_bar_baz, "%s/foo/bar/baz", mpoint);

  int fd = open(foo_bar_baz, O_RDWR | O_TRUNC, 0777);
  if (fd >= 0) {
    write(fd, (char *)buf, 517);
    write(fd, (char *)buf, sizeof(buf));
    close(fd);
  }

  fd = open(foo_bar_baz, O_RDWR | O_TRUNC, 0777);
  if (fd >= 0) {
   write(fd, (char *)buf, sizeof(buf));
    close(fd);
  }
}

int main(int argc, char *argv[]) {
  activity(argv[1]);
  return 0;
}
