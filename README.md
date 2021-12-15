# Command-line-application-for-Task-Management
This repository is about Commandline app made for management of tasks.

## Functions of the Application
1. You can add tasks with their priority like in what order you want the tasks to be completed.
2. You can list all the pending tasks.
3. You can mark the task as completed after the completion of the task.
4. You can delete an unwanted task if you dont want to perform it.
5. You can generate a report of all the pending tasks and all the completed tasks.

----
## All the commands which can be performed on this app
### 1. Help ->
Executing the command without any arguments, or with a single argument help prints the CLI usage.
$ ./task help or $ ./task
Usage :-
$ ./task add 2 hello world    # Add a new item with priority 2 and text "hello world" to the list \n
$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order
$ ./task del INDEX            # Delete the incomplete item with the given index
$ ./task done INDEX           # Mark the incomplete item with the given index as complete
$ ./task help                 # Show usage
$ ./task report               # Statistics

