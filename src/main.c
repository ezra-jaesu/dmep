#include <stdio.h>
#include <string.h>
int main() {
    printf("DMEP has been initialized!\n");

    char command[256];

    while(1) {
	printf("> ");
	fflush(stdout);
	fgets(command, sizeof(command), stdin);

	if (strcmp(command, "quit\n") == 0) {
	    printf("\nQuitting...\n");
	    return 0;
	}

    };



    return 0;
}
