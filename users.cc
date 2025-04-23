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

** Archivo users.cc: Implementacion de la clase User
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      23/04/2025 - Creacion (primera version) del codigo
**/

#include "users.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

User::User(const string& email, const string& username, short role)
  : email_(email), username_(username), role_(role) {
}

const string& User::getEmail() const    { return email_; }
const string& User::getUsername() const { return username_; }
const short int User::getRole() const {return role_;}
const std::vector<Message>& User::getInbox() const {return inbox_;}

// Enviar y recibir
void User::sendMessage(User& recipient, const string& text) {
  Message m{ username_, text, std::chrono::system_clock::now(), false };
  recipient.receiveMessage(m);
}

void User::receiveMessage(const Message& msg) {
    inbox_.push_back(msg);
}

void User::markAsRead(size_t index) {
  if (index < inbox_.size()) inbox_[index].read = true;
}