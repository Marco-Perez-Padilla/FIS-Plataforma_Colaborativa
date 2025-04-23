/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, 
** Correo: alu0101469348@ull.edu.es
** Fecha: 23/04/2025

** Archivo exceptions.h: Declaracion de las clases de excepciones
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      23/04/2025 - Creacion (primera version) del codigo
**/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


/**
 * @brief Class Exceptions that inheritages from std:exception, it has a protected member which is the message to be thrown if an error occurs
 */
class Exceptions : public std::exception {
 protected:
  std::string error_message_;
 public:
  explicit Exceptions (const std::string& error_message) : error_message_(error_message) {}
  const char* what() const throw() {return error_message_.c_str();}
};


/**
 * @brief Class OpenFileException. Throws an exception if size is not 8
 */
class OpenFileException : public Exceptions {
 public:
  explicit OpenFileException(const std::string& file_name) : Exceptions("Error: File " + file_name + " couldn't be opened") {}
};


/**
 * @brief Class NifLongException. Throws an exception if size is greater than 8, or negative number
 */
class AlreadyRegisteredException : public Exceptions {
 public:
  AlreadyRegisteredException() : Exceptions("Error: User already registered") {}
};


/**
 * @brief Class NifLongException. Throws an exception if size is greater than 8, or negative number
 */
class NonRegisteredException : public Exceptions {
 public:
  NonRegisteredException() : Exceptions("Error: User not registered") {}
};


/**
 * @brief Class NifLongException. Throws an exception if size is greater than 8, or negative number
 */
class WrongAnswerException : public Exceptions {
 public:
  WrongAnswerException() : Exceptions("Error: Wrong Answer") {}
};



/**
 * @brief Class ClosedInsertException. Throws an exception if a key couldn't be inserted on a hash table
 */
class WrongPasswordException : public Exceptions {
 public:
  WrongPasswordException() : Exceptions("Error: Incorrect password") {}
};


#endif