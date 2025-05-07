/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, Eduardo Javier Marichal de la Fuente
** Correo: alu0101469348@ull.edu.es
** Fecha: 23/04/2025

** Archivo users.h: Declaracion de la clase User
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      23/04/2025 - Creacion (primera version) del codigo
**      07/05/2025 - Mejoras para la implementacion de bases de datos de usuarios y mensajes
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

// Funciones de persistencia de mensajes en disco
void saveMessageToFile(const std::string& sender,
                       const std::string& recipient,
                       const std::string& content,
                       const std::chrono::system_clock::time_point& ts,
                       bool read_flag);

std::vector<Message> loadMessagesFromFile(const std::string& recipient);

bool userExists(const std::string& email);
void updateMessageReadStatusInFile(const Message& message, const std::string& recipient);

class User {
 private:
  std::string email_;
  std::string username_;
  short int role_; // 0=admin,1=profesor,2=alumno
  std::vector<Message> inbox_;
 public:
  // Constructors
  User() = default;
  User(const std::string& email, const std::string& username, short role = 2);
  
  // Getters
  const std::string& getEmail() const;
  const std::string& getUsername() const;
  const short int getRole() const;
  const std::vector<Message>& getInbox() const;
  
  // Mensajería
  void sendMessage(User& recipient, const std::string& text);
  void receiveMessage(const Message& msg);
  void markAsRead(size_t index);
  void clearInbox();
};

#endif