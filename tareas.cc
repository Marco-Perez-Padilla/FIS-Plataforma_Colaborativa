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


static const char DELIM = '\t';
static const std::string TASK_DB_FILE  = "task.txt";

std::string FormatDate(std::chrono::year_month_day fecha) {
  std::ostringstream os;
  os << static_cast<int>(fecha.year()) << "-"
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(fecha.month()) << "-"
      << std::setw(2) << std::setfill('0') << static_cast<unsigned>(fecha.day());
  return os.str();
}


void Task::ChangeDueDate() {
  int y, m, d;
  std::cout << "Nueva fecha (YYYY MM DD): ";
  std::cin >> y >> m >> d;
  due_date_ = std::chrono::year{y}/m/d;
}


void Task::ChangePriority() {
  std::cout << "Seleccione nuevo estado:\n";
  std::cout << "  0. Low\n";
  std::cout << "  1. Medium\n";
  std::cout << "  2. High\n";
  int option;
  std::cin >> option;

  if (option >= 0 && option <= 3) {
    priority_ = static_cast<Priority>(option);
  } else {
    std::cout << "Estado inválido. No se realizaron cambios.\n";
  }
}


void Task::SaveTask() {
  std::string folder = email_;
  std::filesystem::create_directories(folder);  // Crea la carpeta si no existe

  std::ofstream file(folder + "/tasks.txt");
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo de tareas.\n";
    return;
  }

  file << static_cast<int>(status_) << ' '
  << static_cast<int>(priority_) << ' '
  << static_cast<int>(int(due_date_.year())) << ' '
  << unsigned(due_date_.month()) << ' '
  << unsigned(due_date_.day()) << ' '
  << email_ << '\n'; 

  file.close();
}


Task CreateTask(const std::string& email) {
  std::string name, description;
  int y, m, d;

  std::cout << "Introduce nombre de la tarea: ";
  std::cin >> name;
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
  Task new_task(email, name, date, description);

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
  return new_task;
}

//HU-8 Nuevo
void Task::AddTag(const std::string& tag) {
    tags_.insert(tag);
}

void Task::RemoveTag(const std::string& tag) {
    tags_.erase(tag);
}

bool Task::HasTag(const std::string& tag) const {
    return tags_.find(tag) != tags_.end();
}

bool Task::ContainsKeyword(const std::string& keyword) const {
    return name_.find(keyword) != std::string::npos ||
           description_.find(keyword) != std::string::npos;
}

void Task::Show() const {
    std::cout << "Title: " << titulo << "\nDescription: " << descripcion << "\nTags: ";
    for (const auto& tag : tags)
        std::cout << "[" << tag << "] ";
    std::cout << "\n";
}


std::vector<Task> FilterByTag(const std::vector<Task>& tasks, const std::string& tag) {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (task.HasTag(tag))
            result.push_back(task);
    }
    return result;
}

std::vector<Task> FilterByKeyword(const std::vector<Task>& tasks, const std::string& keyword) {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (task.ContainsKeyword(keyword))
            result.push_back(task);
    }
    return result;
}

// Observación: Es posible que también se pueda hacer llamando al constructor directamente
// Pero haciendo los static_cast fuera.
std::vector<Task> LoadTasksFromFile(const std::string& email) {
  std::vector<Task> tasks;
  std::ifstream file(email + "/tasks.txt");

  if (!file.is_open()) {
    std::cerr << "Could not open task file for user: " << email << "\n";
    return tasks;
  }

  int status, priority, year, month, day;
  while (file >> status >> priority >> year >> month >> day) { //TO DO: Meter también los otros atributos
    Task task(email, "N/A", std::chrono::year{year}/month/day); // Nombre se sustituirá si es necesario
    task.SetStatus(static_cast<Task::Status>(status));
    task.SetPriority(static_cast<Task::Priority>(priority));
    // TO DO: Leer nombre, descripción y tags.
    tasks.push_back(task);
  }

  return tasks;
}


 //HU-8 FIN