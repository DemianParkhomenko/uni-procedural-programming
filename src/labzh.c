#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// long sysconf(int name);

// long pathconf(const char* pathname, int name);

// long fpathconf(int filedes, int name);

int main() {
  printf("\t\tsysconf\n");
  char *sysconfArrayName[32] = {
      "_SC_ARG_MAX",          "_SC_CHILD_MAX",       "_SC_HOST_NAME_MAX",
      "_SC_LOGIN_NAME_MAX",   "_SC_NGROUPS_MAX",     "_SC_CLK_TCK",
      "_SC_OPEN_MAX",         "_SC_PAGESIZE",        "_SC_RE_DUP_MAX",
      "_SC_STREAM_MAX",       "_SC_SYMLOOP_MAX",     "_SC_TTY_NAME_MAX",
      "_SC_TZNAME_MAX",       "_SC_VERSION",         "_SC_BC_BASE_MAX",
      "_SC_BC_DIM_MAX",       "_SC_BC_SCALE_MAX",    "_SC_BC_STRING_MAX",
      "_SC_COLL_WEIGHTS_MAX", "_SC_EXPR_NEST_MAX",   "_SC_LINE_MAX",
      "_SC_RE_DUP_MAX",       "_SC_2_VERSION",       "_SC_2_C_DEV",
      "_SC_2_FORT_DEV",       "_SC_2_FORT_RUN",      "_SC_2_LOCALEDEF",
      "_SC_2_SW_DEV",         "_SC_PHYS_PAGES",      "_SC_AVPHYS_PAGES",
      "_SC_NPROCESSORS_CONF", "_SC_NPROCESSORS_ONLN"};
  long int sysconfArrayValue[32] = {
      _SC_ARG_MAX,          _SC_CHILD_MAX,       _SC_HOST_NAME_MAX,
      _SC_LOGIN_NAME_MAX,   _SC_NGROUPS_MAX,     _SC_CLK_TCK,
      _SC_OPEN_MAX,         _SC_PAGESIZE,        _SC_RE_DUP_MAX,
      _SC_STREAM_MAX,       _SC_SYMLOOP_MAX,     _SC_TTY_NAME_MAX,
      _SC_TZNAME_MAX,       _SC_VERSION,         _SC_BC_BASE_MAX,
      _SC_BC_DIM_MAX,       _SC_BC_SCALE_MAX,    _SC_BC_STRING_MAX,
      _SC_COLL_WEIGHTS_MAX, _SC_EXPR_NEST_MAX,   _SC_LINE_MAX,
      _SC_RE_DUP_MAX,       _SC_2_VERSION,       _SC_2_C_DEV,
      _SC_2_FORT_DEV,       _SC_2_FORT_RUN,      _SC_2_LOCALEDEF,
      _SC_2_SW_DEV,         _SC_PHYS_PAGES,      _SC_AVPHYS_PAGES,
      _SC_NPROCESSORS_CONF, _SC_NPROCESSORS_ONLN};
  // printf("%d",sizeof(array)/sizeof(array[0]));
  for (int i = 0; i < sizeof(sysconfArrayValue) / sizeof(sysconfArrayValue[0]);
       i++) {
    printf("Значення границі %s дорівнює %ld.\n", sysconfArrayName[i],
           sysconf(sysconfArrayValue[i]));
  };

  printf("\t\tpathconf\n");
  char *pathconfArrayName[9] = {
      "_PC_LINK_MAX",         "_PC_MAX_CANON", "_PC_MAX_INPUT",
      "_PC_NAME_MAX",         "_PC_PATH_MAX",  "_PC_PIPE_BUF",
      "_PC_CHOWN_RESTRICTED", "_PC_NO_TRUNC",  "_PC_VDISABLE",

  };
  long int pathconfArrayValue[9] = {
      _PC_LINK_MAX,         _PC_MAX_CANON, _PC_MAX_INPUT,
      _PC_NAME_MAX,         _PC_PATH_MAX,  _PC_PIPE_BUF,
      _PC_CHOWN_RESTRICTED, _PC_NO_TRUNC,  _PC_VDISABLE,

  };

  for (int i = 0;
       i < sizeof(pathconfArrayValue) / sizeof(pathconfArrayValue[0]); i++) {
    printf("Значення %s границі дорівнює %ld.\n", pathconfArrayName[i],
           pathconf(".", pathconfArrayValue[i]));
  };

  int fd;
  fd = open("fieldTest.txt", O_RDONLY);
  printf("\t\tfpathconf\n");
  for (int i = 0;
       i < sizeof(pathconfArrayValue) / sizeof(pathconfArrayValue[0]); i++) {
    printf("Значення границі %s дорівнює %ld.\n", pathconfArrayName[i],
           fpathconf(fd, pathconfArrayValue[i]));
  };

  return 0;
}