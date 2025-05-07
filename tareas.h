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

** Archivo tareas.h: Declaracion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      07/05/2025 - Creacion (primera version) del codigo
**/

#ifndef TAREAS_H
#define TAREAS_H

#include <string>
#include <chrono>
#include <vector>

#include "users.h"

enum Priority {
  low,    // 0
  medium, // 1
  high    // 2
};


enum Status {
  pending,  // 0
  done,     // 1 
  delayed   // 2
};


class Task {
 private:
  std::string email_;
  std::string name_;
  std::chrono::year_month_day due_date_;
  Status status_;
  Priority priority_;
 public:
  // Constructors
  Task(std::string email, std::string name, std::chrono::year_month_day due_date, Status status = Status::pending, Priority priority = Priority::low) 
  : email_(email), name_(name), due_date_(due_date), status_(status), priority_(priority) {}
  // Getters
  const std::string& getUserEmail() const {return email_;}
  const std::chrono::year_month_day& getDueDate() const {return due_date_;}
  const Status& getStatus() const {return status_;}
  const Priority& getPriority() const {return priority_;}
  // Manage Task methods
  void ChangeDueDate();
  void ChangeStatus(); // Change status cambia automaticamente dependiendo de la fecha, conexion con HU 9
  void ChangePriority();
  // Save and read task methods
  void SaveTask();
      // Los métodos de lectura serían los de filtrado y búsqueda del HU 8
  
      // O sea, despues de tener la HU 8 podemos hacer un menu que busque una tarea, que el usuario inserte el nombre, y que pueda cambiar su prioridad 
      // si es alumno, y la fecha de entrega si es profesor (se puede controlar por los menus eso) o algo asi
};


std::string FormatDate(std::chrono::year_month_day); // Para imprimir una fecha, usar esta funcion, para poder imprimir el string
Task CreateTask(const std::string&);

#endif