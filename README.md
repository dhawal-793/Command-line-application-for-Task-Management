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
Executing the command without any arguments, or with a single argument help prints the CLI usage.<br>
<pre>$ ./task help or $ ./task
Usage :-
$ ./task add 2 hello world   --> # Add a new item with priority 2 and text "hello world" to the list
$ ./task ls                  --> # Show incomplete priority list items sorted by priority in ascending order
$ ./task del INDEX           --> # Delete the incomplete item with the given index
$ ./task done INDEX          --> # Mark the incomplete item with the given index as complete
$ ./task help                --> # Show usage
$ ./task report              --> # Statistics</pre><br>

### 2. Add ->
Use the add command. The text of the task should be enclosed within double quotes (otherwise only the first word is considered as the item text, and the remaining words are treated as different arguments).<br>
<pre>$ ./task add 5 "the thing i need to do"
Added task: "the thing i need to do" with priority 5</pre><br>

### 3. list ->
Use the ls command to see all the items that are not yet complete, in ascending order of priority.<br>
<pre>$ ./task ls
1. change light bulb [2]
2. water the plants [5]</pre><br>

### 4. Delete ->
Use the del command to remove an item by its index.<br>
<pre>$ ./task del 3
Deleted item with index 3</pre><br>

### 5. Done ->
Use the done command to mark an item as completed by its index.<br>
<pre>$ ./task done 1
Marked item as done.</pre><br>

### 6. Report ->
Show the number of complete and incomplete items in the list. and the complete and incomplete items grouped together.<br>
<pre>$ ./task report
Pending : 2
1. this is a pending task [1]
2. this is a pending task with priority [4]

Completed : 3
1. completed task
2. another completed task
3. yet another completed task</pre><br>
