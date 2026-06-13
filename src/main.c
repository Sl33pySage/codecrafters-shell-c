#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#define PATH_LIST_SEPARATOR ";"
#else
#define PATH_LIST_SEPARATOR ":"
#endif /* ifdef _WIN32 */

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  char command[1024];

  while (1) {
    printf("$ ");

    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    // 1. Create a mutable pointer variable to the start of the buffer
    char *search_ptr = command;

    // 2. Pass the ADDRESS of that pointer variable  (&search_ptr)
    // strsep will automatically advance search_ptr to the next token
    char *builtin = strsep(&search_ptr, " ");
    char *arg = strsep(&search_ptr, ""); // Grabs everything left in the string
    // char *builtin = strtok(command, " "); OLD STRTOK WAY
    // char *arg = strtok(NULL, ""); OLD STRTOK WAY

    if (builtin == NULL)
      continue;

    if (strcmp(builtin, "exit") == 0) {
      break;
    } else if (strcmp(builtin, "echo") == 0) {
      printf("%s\n", arg);
    } else if (strcmp(builtin, "type") == 0) {
      if (!strcmp(arg, "exit") || !strcmp(arg, "echo") ||
          !strcmp(arg, "type")) {
        printf("%s is a shell builtin\n", arg);
      }
    }
  }
}
