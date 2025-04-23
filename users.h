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
#include <vector>
#include <chrono>

/**
 * Mensaje simple: emisor, contenido, fecha y estado de lectura.
 */
struct Message {
  std::string sender;
  std::string content;
  std::chrono::system_clock::time_point timestamp;
  bool read = false;
};

class User {
 private:
  std::string email_;
  std::string username_;
  int short role_; // 0=admin,1=profesor,2=alumno
  std::vector<Message> inbox_;
 public:
  // Constructors
  User() = default;
  User(const std::string& email,
    const std::string& username,
    short role = 2);
  
  // Getters
  const std::string& getEmail() const;
  const std::string& getUsername() const;

  // Mensajería
  void sendMessage(User& recipient, const std::string& text);
  void receiveMessage(const Message& msg);
  const std::vector<Message>& getInbox() const;
  void markAsRead(size_t index);
};

#endif