/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 7: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, /////
** Correo: alu0101469348@ull.edu.es
** Fecha: 21/04/2025

** Archivo tareas.cc: Implementacion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      07/05/2025 - Creacion (primera version) del codigo
**/

#include <iostream>
#include <fstream>
#include <filesystem>  

#include "tareas.h"

static const std::string TASK_DB_FILE  = "task.txt"; // File where tasks will be located

/**
 * @brief Overload of operator << to show in terminal a Task
 * @param ostream os
 * @param Task task to be displayed
 * @return ostream
 */
std::ostream& operator<<(std::ostream& os, const Task& task) {
  os << "--------------------------------------\n";
  os << "Tarea: " << task.getTitle() << "\n";
  os << "Descripción: " << task.getDescription() << "\n";

  os << "Fecha de entrega: " << FormatDate(task.getDueDate()) << "\n";

  os << "Prioridad: ";
  switch (task.getPriority()) {
    case Priority::low: os << "Low"; break;
    case Priority::medium: os << "Medium"; break;
    case Priority::high: os << "High"; break;
  }
  os << "\n";

  os << "Estado: ";
  switch (task.getStatus()) {
    case Status::pending: os << "Pending"; break;
    case Status::done: os << "Done"; break;
    case Status::delayed: os << "Delayed"; break;
  }
  os << "\n";

  os << "Etiquetas: ";
  if (task.getTags().empty()) {
    os << "(ninguna)";
  } else {
    for (const auto& tag : task.getTags()) {
      os << "[" << tag << "] ";
    }
  }
  os << "\n";

  os << "Usuario: " << task.getUserEmail() << "\n";
  os << "--------------------------------------\n";
  return os;
}


/**
 * @brief Auxiliar function that transforms a date into a string
 * @param std::chrono::year_month_day date
 * @return date in string type
 */
std::string FormatDate(std::chrono::year_month_day fecha) {
  std::ostringstream os;
  os << static_cast<int>(fecha.year()) << "-"
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(fecha.month()) << "-"
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(fecha.day());
  return os.str();
}


/**
 * @brief Method that allows to change the due date of a task
 */
void Task::ChangeDueDate() {
  int y, m, d;
  std::cout << "Nueva fecha (YYYY MM DD): ";
  std::cin >> y >> m >> d;
  due_date_ = std::chrono::year{y}/m/d;
}


/**
 * @brief Method that allows to change the priority of a task
 */
void Task::ChangePriority() {
  std::cout << "Seleccione nuevo estado:\n";
  std::cout << "  0. Low\n";
  std::cout << "  1. Medium\n";
  std::cout << "  2. High\n";
  int option;
  std::cin >> option;

  if (option >= 0 && option <= 2) {
    priority_ = static_cast<Priority>(option);
  } else {
    std::cout << "Estado inválido. No se realizaron cambios.\n";
  }
}


/**
 * @brief Method that saves a task into TASK_DB_FILE, in a folder for each user
 */
void Task::SaveTask() {
  std::string folder = email_;
  std::filesystem::create_directories(folder);  // Crea la carpeta si no existe

  std::ofstream file(folder + "/tasks.txt", std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo de tareas.\n";
    return;
  }

  file << static_cast<int>(status_) << ' '
  << static_cast<int>(priority_) << ' '
  << static_cast<int>(int(due_date_.year())) << ' '
  << unsigned(due_date_.month()) << ' '
  << unsigned(due_date_.day()) << ' '
  << title_ << ' '
  << description_ << ' '
  << email_ << ' ';
  for (const auto& tag : tags_) {
    file << tag << ',';
  }
  file << '\n'; 

  file.close();
}


/**
 * @brief Method that allows a user to create a task, assigning it to one or more users
 * @param string email of the user that will get the new task assigned
 * @return Task created
 */
Task CreateTask(const std::string& email) {
  std::string title, description;
  int y, m, d;

  std::cout << "Introduce nombre de la tarea: ";
  std::cin >> title;
  //HU-08 Nuevo
  std::cout << "Introduce una breve descripción de la tarea: ";
  std::cin >> description;
  //HU-08 Fin
  std::cout << "Introduce fecha de entrega (YYYY MM DD): ";
  std::cin >> y >> m >> d;

  std::chrono::year_month_day date{
    std::chrono::year{y},
    std::chrono::month{m},
    std::chrono::day{d}
  };
  Task new_task(email, title, date, description);

  //HU-08 Nuevo
  std::cout << "¿Quieres añadir etiquetas a la tarea? (y/n): ";
  char opt;
  std::cin >> opt;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (opt == 'y' || opt == 'Y') {
    std::string tag;
    while (true) {
      std::cout << "Enter tag (or type 'done' to finish): ";
      std::getline(std::cin, tag);
      if (tag == "done") break;
      if (tag.empty()) {
        std::cout << "Tag cannot be empty.\n";
        continue;
      }
      new_task.AddTag(tag);
    }
  }
  //HU-08 FIN
  new_task.SaveTask();
  return new_task;
}

//HU-8 Nuevo
/**
 * @brief Method that adds a tag to a task
 * @param string tag
 */
void Task::AddTag(const std::string& tag) {
  tags_.insert(tag);
}


/**
 * @brief Method to remove a specified tag from a task
 * @param string tag to be removed
 */
void Task::RemoveTag(const std::string& tag) {
  tags_.erase(tag);
}


/**
 * @brief Method that checks if a task has a certain tag or not
 * @param string tag to be found
 * @return bool-type. True if found, false otherwise
 */
bool Task::HasTag(const std::string& tag) const {
  return tags_.find(tag) != tags_.end();
}


/**
 * @brief Metod to check if a task has a keyword in either its title or its description
 * @param string keyword to be found
 * @return bool-type. True if found, false otherwise
 */
bool Task::ContainsKeyword(const std::string& keyword) const {
  return title_.find(keyword) != std::string::npos ||
        description_.find(keyword) != std::string::npos;
}


// void Task::Show() const {
//   std::cout << "Title: " << title_ << "\nDescription: " << description_ << "\nTags: ";
//   for (const auto& tag : tags_)
//     std::cout << "[" << tag << "] ";
//   std::cout << "\n";
// }


/**
 * @brief Function that filters tasks using a tag
 * @param vetor of tasks: Vector to be filtered
 * @param string tag to be used in the filter
 * @return result of the filter, vector of tasks 
 */
std::vector<Task> FilterByTag(const std::vector<Task>& tasks, const std::string& tag) {
  std::vector<Task> result;
  for (const auto& task : tasks) {
    if (task.HasTag(tag))
      result.push_back(task);
  }
  return result;
}


/**
 * @brief Function that filters tasks using a keyword
 * @param vector of tasks: Vector to be filtered
 * @param string tag to be used in the filter
 * @return result of the filter, vector of tasks 
 */
std::vector<Task> FilterByKeyword(const std::vector<Task>& tasks, const std::string& keyword) {
  std::vector<Task> result;
  for (const auto& task : tasks) {
    if (task.ContainsKeyword(keyword))
      result.push_back(task);
  }
  return result;
}


/**
 * @brief Method that reads all the tasks of the user
 * @param string email that identifies the user
 * @return vector with all the tasks
 */
std::vector<Task> LoadTasksFromFile(const std::string& email) {
  std::vector<Task> tasks;
  std::ifstream file(email + "/tasks.txt");

  if (!file.is_open()) {
    std::cerr << "Could not open task file for user: " << email << "\n";
    return tasks;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    int status, priority, year, month, day;
    std::string title, description, tags, email;

    if (!(iss >> status >> priority >> year >> month >> day >> title >> description >> email)) {
      std::cerr << "Error leyendo campos de la tarea.\n";
      continue;
    }

    std::getline(iss, tags);
    std::istringstream tags_stream(tags);

    std::string tag;
    std::set<std::string> tags_set;
    while (std::getline(tags_stream, tag, ',')) {
      if (!tag.empty()) {
        tags_set.insert(tag);
      }
    }

    std::chrono::year_month_day date = std::chrono::year{year} / std::chrono::month{month} / std::chrono::day{day};
    Task task(email, title, date, description, static_cast<Status>(status), static_cast<Priority>(priority));

    for (const auto& tg : tags_set) {
      task.AddTag(tg);
    }
    tasks.push_back(task);
  }
  return tasks;
}


 //HU-8 FIN