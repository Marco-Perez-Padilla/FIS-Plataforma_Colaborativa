/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, /////
** Correo: alu0101469348@ull.edu.es
** Fecha: 23/04/2025

** Archivo users.h: Declaracion de la clase User
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      23/04/2025 - Creacion (primera version) del codigo
**/

#ifndef USERS_H
#define USERS_H

#include <string>


class User {
 private:
  std::string email_;
  std::string username_;
  int short role_; // Podría cambiarse por un enum o struct. 0, 1 y 2. Admin, profesor, alumno (orden el que sea)
 public:
  // Constructors
  User() = default;
  User(const std::string& email, const std::string& username, const int short role = 0) : email_(email), username_(username), role_(role) {} // Rol por defecto cambiarlo a estudiante
  // Getters
  const std::string& getEmail() const {return email_;}
  const std::string& getUsername() const {return username_;}
};

#endif