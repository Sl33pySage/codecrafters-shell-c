#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // A REPL (Read-Eval-Print-Loop) is an interactive loop that forms the core of
  // a shell. It follows a repeating cycle:
  while (1) {
    // Wait for user input
    char input[100];
    // 1. Read: Display a prompt and wait for user input.
    printf("$ ");
    fgets(input, 100, stdin);
    // 2. Eval: Parse and execute the command.

    // Remove the trailing new line
    input[strlen(input) - 1] = '\0';

    // 3. Print: Display the output or error message.
    if (strcmp(input, "exit") == 0) {
      break; // Exit the shell
    } else if (strncmp(input, "echo", 5) == 0) {
      printf("%s\n", input + 5);
      break;
    } else {
      printf("%s: command not found\n", input);
    }
    // 4. Loop: Return to step 1 and wait for the next command.
  }
  return 0;
}
