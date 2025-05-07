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
  std::string name;
  int y, m, d;

  std::cout << "Introduce nombre de la tarea: ";
  std::cin >> name;

  std::cout << "Introduce fecha de entrega (YYYY MM DD): ";
  std::cin >> y >> m >> d;

  std::chrono::year_month_day date{
    std::chrono::year{y},
    std::chrono::month{m},
    std::chrono::day{d}
  };

  Task new_task(email, name, date);
  return new_task;
}
