#include "clog.hpp"

void usage() { printf("Usage: Tool.exe <FileName> <Filter>\n"); }

int main(int argc, char *argv[]) {
  char line[4096];

  if (argc != 3) {
    usage();
    return -1;
  }

  filter::CLogReader log;
  if (!log.Open(argv[1])) {
    printf("Open filename %s error\n", argv[1]);
    return -1;
  }

  if (!log.SetFilter(argv[2])) {
    printf("Set filter %s error\n", argv[2]);
    return -1;
  }

  while (log.GetNextLine(line, sizeof(line))) {
    printf("%s", line);
  }

  return 0;
}
