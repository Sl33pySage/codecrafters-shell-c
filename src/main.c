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

    char *builtin = strtok(command, " ");
    char *arg = strtok(NULL, "");
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
        break;
      } else {
        char *path_env = getenv("PATH");
        // A buffer for the path I can traverse and do string manipulation on
        char *pathbuf = strtok(path_env, PATH_LIST_SEPARATOR);

        if (path_env != NULL) {

          // printf("Current Path:\n%s\n", path_env);
          while (pathbuf != NULL) {
            printf("PathBuf:\n%s\n", pathbuf);
            pathbuf = strtok(NULL, PATH_LIST_SEPARATOR);
            // access(arg, X_OK) == 0 ||
            if (strcmp(arg, pathbuf)) {
              printf("Success: file \narg: %s exists in \npathbuf: %s and "
                     "has execution "
                     "permissions.\n",
                     arg, pathbuf);
              break;
            }
          }

        } else {
          printf("PATH env var is not found\n");
        }
      }
      printf("%s: not found\n", arg);

    } else {
      printf("%s: command not found\n", builtin);
    }
  }
  return 0;
}
