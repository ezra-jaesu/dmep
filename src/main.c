#include <stdio.h> 
#include <string.h>

const char CHAR_CORRECTION_FOR_NUMBERS = 48;

typedef struct {
    char desc[32];
    char done;
} Mep;

typedef struct {
    short start_time;
    short duration;
    short reminder;
    char name[32];
    Mep mep[3];
} Task; 

Task create_task() {
    Task task;
    strcpy(task.name, "");
    task.start_time = -1;
    task.duration = 0;
    task.reminder = 0;
    return task;
}

void set_time(char *time, Task *task) {
    // Since we're only dealing with one day, we can just count the time from midnight.
    // The range of time is 0 -> 1440
    char PM_CORRECTION = 0;
    char EXTRA_DIGIT_CORRECTION = 0; 
    
    // if there's p in time, adjust time_minutes for night 
    if (time[strcspn(time, "p")] == 'p') PM_CORRECTION = 12; 
    // if there's x in time, adjust time for double digit hours
    if (time[strcspn(time, "x")] == 'x') EXTRA_DIGIT_CORRECTION = 1; 


    //set the hours
    short time_minutes = (time[0] - CHAR_CORRECTION_FOR_NUMBERS + PM_CORRECTION) * 60;
    if (time[1] && time[1] >= '0' && time[1] <= '9') time_minutes += ((time[1] - CHAR_CORRECTION_FOR_NUMBERS) % 6) * 10;
    // set minutes on ones
    if (time[1] && time[2] >= '0' && time[2] <= '9') time_minutes += (time[2] - CHAR_CORRECTION_FOR_NUMBERS);

    if (EXTRA_DIGIT_CORRECTION) {
	time_minutes = (time[1] == '2') ? PM_CORRECTION * 60 : (10 + time[1] - CHAR_CORRECTION_FOR_NUMBERS + PM_CORRECTION) * 60;	
	if (time[3] && time[2] >= '0' && time[2] <= '9') time_minutes += ((time[2] - CHAR_CORRECTION_FOR_NUMBERS) % 6) * 10;
	if (time[3] && time[3] >= '0' && time[3] <= '9') time_minutes += (time[2] - CHAR_CORRECTION_FOR_NUMBERS); 
    }

    // if start_time exists, set duration instead
    if (task->start_time != -1) {
	task->duration = time_minutes - task->start_time;

	if (task->start_time > time_minutes) task->start_time = time_minutes;
	if (task->duration < 0) task->duration *= -1;

	return;
    }

    task->start_time = time_minutes; 
}

int main() {
    printf("DMEP has been initialized!\n");

    char command[128];
    char *tokens[16];
    char *tasks[10];
    while(1) {
	int index = 0;

	printf("> ");
	fflush(stdout);
	fgets(command, sizeof(command), stdin);

	command[strcspn(command, "\n")] = 0;

	// Basically loop again if user tries to fuck you over.
	if (!command[0]) continue;

	if (strcmp(command, "quit") == 0) {
	    printf("\nQuitting...\n");
	    return 0;
	}


	// add 8p 9p Watch Gura !15
	// 0   1  2   3     4    5
	char *save_token;
	char *token = strtok_r(command, " ", &save_token);
	if (strcmp(token, "add") == 0) {
	    printf("\nAdding...\n");
	    Task new_task = create_task();
	    token = strtok_r(NULL, " ", &save_token);
	    set_time(token, &new_task);
	    token = strtok_r(NULL, " ", &save_token);
	    set_time(token, &new_task);
	    strcpy(new_task.name, save_token);
	    printf("Start %s, %d minutes after midnight and ends after %d minutes \n",new_task.name, new_task.start_time, new_task.duration);

	}

    };


    

    return 0;
}
