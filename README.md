To-Do List Application

Introduction

This is a console-based to-do list application written in C++. It allows users to manage their tasks by adding new tasks, viewing all tasks with their completion status, and marking tasks as completed. The application uses a simple menu-driven interface and includes data persistence, saving tasks to a text file so they persist between sessions.
Features
Add New Tasks: Users can input task descriptions to add them to the list.
View All Tasks: Displays tasks with a number, completion status ([x] for completed, [ ] for pending), and description.

Mark Tasks as Completed: Users can mark a task as completed by entering its number.
User-Friendly Display: Tasks are shown in a clean, numbered format in the terminal.
Data Persistence: Tasks are saved to tasks.txt and loaded when the application starts.

How to Use

Compile the Code: Use a C++ compiler, e.g., g++ -o todo todo.cpp.
Run the Application: Execute the compiled program, e.g., ./todo.
Navigate the Menu: Choose an option by typing its number and pressing Enter:

1. Add a new task: Type a task description and press Enter.
2. View all tasks: See the list of tasks with their status.
3. Mark a task as completed: Enter the task number to mark it as done.
4. Exit: Save tasks and close the application.

Code Structure

Task Class: Represents a task with a description (string) and completed status (boolean).

addTask Function: Prompts for a description and adds a new task to the list, ensuring it’s not empty.

viewTasks Function: Displays all tasks or a "No tasks available" message if the list is empty.
markCompleted Function: Marks a task as completed based on user input, with error handling for invalid inputs.

loadTasks Function: Reads tasks from tasks.txt at startup.

saveTasks Function: Writes tasks to tasks.txt when exiting.

main Function: Manages the menu loop, processes user choices, and handles task persistence.

Data Persistence
File: Tasks are stored in tasks.txt.
Format: Each line is status,description, where status is 0 (pending) or 1 (completed), followed by a comma and the task description.
Behavior: Loaded at startup; saved on exit. If the file doesn’t exist initially, it starts empty and creates the file on the first save.
