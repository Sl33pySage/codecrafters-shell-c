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

    char *saveptr;
    char *path_env = getenv("PATH");
    char *path_copy = strdup(path_env);
    char *token = strtok_r(path_copy, PATH_LIST_SEPARATOR, &saveptr);
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

      } else {
        // char *path_env = getenv("PATH");
        // char *token = strtok(path_env, PATH_LIST_SEPARATOR);

        while (token != NULL && strcmp(token, arg) != 0) {
          token = strtok_r(NULL, "/", &saveptr);
          printf("Checking token: %s\n", token);
          if (token != NULL && strcmp(token, arg) == 0 &&
              access(token, X_OK) == 0) {
            printf(" --> Match found! '%s' is equal to '%s'\n", token, arg);
          }
          token = strtok_r(NULL, "/", &saveptr);
        }
        free(path_copy);
      }
    } else {
      printf("%s: command not found\n", builtin);
    }
  }
  return 0;
}
