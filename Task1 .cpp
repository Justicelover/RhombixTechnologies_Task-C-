#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef> // for size_t

class Task {
public:
    std::string description;
    bool completed;
    Task(std::string desc) : description(desc), completed(false) {}
};

void addTask(std::vector<Task>& tasks) {
    std::cout << "Enter task description: ";
    std::string desc;
    std::getline(std::cin, desc);
    if (desc.empty()) {
        std::cout << "Description cannot be empty." << std::endl;
        return;
    }
    tasks.push_back(Task(desc));
    std::cout << "Task added." << std::endl;
}

void viewTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available." << std::endl;
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "Task " << i + 1 << ": ";
        if (tasks[i].completed) {
            std::cout << "[x] ";
        } else {
            std::cout << "[ ] ";
        }
        std::cout << tasks[i].description << std::endl;
    }
}

void markCompleted(std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks to mark as completed." << std::endl;
        return;
    }
    std::cout << "Enter the task number to mark as completed: ";
    std::string input;
    std::getline(std::cin, input);
    try {
        size_t index = std::stoi(input) - 1;
        if (index >= tasks.size()) {
            std::cout << "Invalid task number." << std::endl;
            return;
        }
        if (tasks[index].completed) {  // Fixed: changed 'i' to 'index'
            std::cout << "Task is already completed." << std::endl;
        } else {
            tasks[index].completed = true;
            std::cout << "Task marked as completed." << std::endl;
        }
    } catch (const std::invalid_argument&) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "Task number out of range." << std::endl;
    }
}

void loadTasks(std::vector<Task>& tasks) {
    std::ifstream file("tasks.txt");
    if (!file.is_open()) {
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string statusStr = line.substr(0, commaPos);
            std::string desc = line.substr(commaPos + 1);
            bool completed = (statusStr == "1");
            Task task(desc);
            task.completed = completed;
            tasks.push_back(task);
        }
    }
    file.close();
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    for (const auto& task : tasks) {
        file << (task.completed ? "1" : "0") << "," << task.description << std::endl;
    }
    file.close();
}

int main() {
    std::vector<Task> tasks;
    loadTasks(tasks);
    std::string choice;
    while (true) {
        std::cout << "\nTo-Do List Application\n";
        std::cout << "1. Add a new task\n";
        std::cout << "2. View all tasks\n";
        std::cout << "3. Mark a task as completed\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, choice);
        if (choice == "1") {
            addTask(tasks);
        } else if (choice == "2") {
            viewTasks(tasks);
        } else if (choice == "3") {
            markCompleted(tasks);
        } else if (choice == "4") {
            saveTasks(tasks);
            std::cout << "Exiting application." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}