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

** Archivo users.cc: Implementacion de la clase User
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      23/04/2025 - Creacion (primera version) del codigo
**      07/05/2025 - Mejoras para la implementacion de bases de datos de usuarios y mensajes
**/

#include "users.h"
#include "exceptions.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

static const char DELIM = '\t';
static const std::string MESSAGE_FILE = "messages.txt";
static const std::string DATA_BASE_FILE = "data_base.txt";

User::User(const std::string& email, const std::string& username, short role) : email_(email), username_(username), role_(role) {}

void saveMessageToFile(const std::string& sender,
                       const std::string& recipient,
                       const std::string& content,
                       const std::chrono::system_clock::time_point& ts,
                       bool read_flag) {
  std::ofstream ofs(MESSAGE_FILE, std::ios::app);
  if (!ofs) throw OpenFileException(MESSAGE_FILE);
  auto t = std::chrono::system_clock::to_time_t(ts);
  ofs << recipient << DELIM
      << sender    << DELIM
      << t         << DELIM
      << (read_flag ? '1' : '0') << DELIM
      << content   << "\n";
}

std::vector<Message> loadMessagesFromFile(const std::string& recipient) {
  std::vector<Message> result;
  std::ifstream ifs(MESSAGE_FILE);
  if (!ifs) return result;
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    std::string rec, snd, t_str, read_str, content;
    if (!std::getline(iss, rec, DELIM) || rec != recipient) continue;
    std::getline(iss, snd,    DELIM);
    std::getline(iss, t_str,  DELIM);
    std::getline(iss, read_str, DELIM);
    std::getline(iss, content);
    Message msg;
    msg.sender    = snd;
    msg.content   = content;
    msg.timestamp = std::chrono::system_clock::from_time_t(std::stoll(t_str));
    msg.read      = (read_str == "1");
    result.push_back(msg);
  }
  return result;
}

void updateMessageReadStatusInFile(const Message& message,
                                   const std::string& recipient) {
  std::ifstream ifs(MESSAGE_FILE);
  if (!ifs) return;
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(ifs, line)) lines.push_back(line);
  ifs.close();
  std::ofstream ofs(MESSAGE_FILE, std::ios::trunc);
  for (auto& l : lines) {
    std::istringstream iss(l);
    std::string rec, snd, t_str, read_str, content;
    std::getline(iss, rec, DELIM);
    std::getline(iss, snd, DELIM);
    std::getline(iss, t_str, DELIM);
    std::getline(iss, read_str, DELIM);
    std::getline(iss, content);
    if (rec == recipient
        && snd == message.sender
        && t_str == std::to_string(std::chrono::system_clock::to_time_t(message.timestamp))
        && content == message.content) {
      ofs << rec << DELIM << snd << DELIM << t_str << DELIM << '1' << DELIM << content << "\n";
    } else {
      ofs << l << "\n";
    }
  }
}

void User::sendMessage(User& recipient, const std::string& text) {
  Message msg;
  msg.sender    = username_;  
  msg.content   = text;
  msg.timestamp = std::chrono::system_clock::now();
  msg.read      = false;
  saveMessageToFile(msg.sender, recipient.getEmail(), msg.content, msg.timestamp, msg.read);
  recipient.receiveMessage(msg);
}

void User::receiveMessage(const Message& msg) {
  inbox_.push_back(msg);
}

void User::markAsRead(size_t idx) {
  if (idx < inbox_.size() && !inbox_[idx].read) {
    inbox_[idx].read = true;
    updateMessageReadStatusInFile(inbox_[idx], email_);
  }
}

void User::clearInbox() {
  inbox_.clear();
}

const std::string& User::getEmail() const {
  return email_;
}

const std::string& User::getUsername() const {
  return username_;
}

const short int User::getRole() const {
  return role_;
}

const std::vector<Message>& User::getInbox() const {
  return inbox_;
}