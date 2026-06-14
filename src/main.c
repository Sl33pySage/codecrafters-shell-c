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

    else if (strcmp(builtin, "exit") == 0) {
      break;
    } else if (strcmp(builtin, "echo") == 0) {
      printf("%s\n", arg);
    } else if (strcmp(builtin, "type") == 0) {
      if (!strcmp(arg, "exit") || !strcmp(arg, "echo") ||
          !strcmp(arg, "type")) {
        printf("%s is a shell builtin\n", arg);
      } else {
        char *path = getenv("PATH");
        char *copied_path = strdup(path);
        char *tokenized_path = strtok(copied_path, ":");
        // char *chopped_path = strtok(tokenized_path, "/");
        //  printf("copied_path: %s\n", copied_path);
        //  printf("s %s\n", s);
        //  printf("chopped_path: %s\n", chopped_path);
        for (int i = 0; i < sizeof(copied_path); i++) {
          tokenized_path = strtok(NULL, ":");
          printf("tokenized_path after strtok: %s\n", tokenized_path);
          if (strcmp(arg, tokenized_path) == 0) {
            printf("%s is in %s\n", arg, tokenized_path);
          }
        }
      }
    }
  }
}
