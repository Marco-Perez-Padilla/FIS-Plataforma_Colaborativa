/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, /////
** Correo: alu0101469348@ull.edu.es
** Fecha: 21/04/2025

** Archivo login.cc: Implementacion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

#include "login.h"


/**
 * @brief Cyphers a password given a preselected key
 * @param string password in plain text to be encrypted
 * @param string key which will be used to encrypt the password
 * @return cyphered password
 */
std::string KeyCypher(const std::string& password, const std::string& key) {
  std::string result;
  for (unsigned int i = 0; i < password.size(); ++i) {
    char text_char = password[i];
    char key_char = key[i % key.size()];

    char shifted = text_char + (key_char % 5); 
    result += shifted;
  }
  return result;
}


/**
 * @brief Cyphers a password with a given shift by using Caesar Cypher method
 * @param string password to be encrypted
 * @param int shift used to encrypt the password
 * @return cyphered password
 */
std::string CaesarCypher(const std::string& password, int shift) {
  std::string result;
  for (char chr : password) {
    result += chr + shift; 
  }
  return result;
}


/**
 * @brief Encrypts a password by combining the Cyphers above implemented
 * @param string password to be encrypted
 * @param string key to be used in the key cypher
 * @param int shift used in the Caesar cypher
 * @return encrypted password
 */
std::string Encrypt(const std::string& password, const std::string& key, int shift) {
  std::string key_cyphered = KeyCypher(password, key);
  std::string caesar_cyphered = CaesarCypher(key_cyphered, shift);
  return caesar_cyphered;
}


/**
 * @brief Decrypts a password created by combining the Cyphers above implemented
 * @param string password to be decrypted
 * @param string key to be used in the key cypher
 * @param int shift used in the Caesar cypher
 * @return decrypted password
 */
std::string Decrypt(const std::string& encrypted, const std::string& key, int shift) {
  std::string caesar_decyphered;
  for (char chr : encrypted) {
    caesar_decyphered += chr - shift;
  }

  std::string original;
  for (size_t i = 0; i < caesar_decyphered.size(); ++i) {
    char key_char = key[i % key.size()];
    char originalChar = caesar_decyphered[i] - (key_char % 5);
    original += originalChar;
  }

  return original;
}


/**
 * @brief Verifies if a password if valid. It must contain upper and lower case, number, special character and minimum of 8 size
 * @param string password to be checked 
 * @return true if the password is valid, false otherwise
 */
bool VerifyValidPassword(const std::string& password) {
  // Explanation:
  // - (?=.*[a-z]) → At least one lower case
  // - (?=.*[A-Z]) → At least one upper case
  // - (?=.*\\d)  → At least one number
  // - (?=.*[^a-zA-Z\\d]) → At least one special character 
  // - .{8,} → Minimum 8 characters

  std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^a-zA-Z\\d]).{8,}$");
  return std::regex_match(password, pattern);
}


/**
 * @brief Sign ups a user with email and password (This function is on construction, it'll have to assign roles to the user)
 * @param string email of the user
 * @param string password of the user
 * @param string name of the file that stores the encrypted passwords
 */
void SignUpUser(const std::string& email, const std::string& password, std::string& password_file) {
  std::string copy_password = password;
  std::ofstream passwd(password_file, std::ios::app);

  if (!passwd.is_open()) {
    // ERROR
  } 

  if (VerifyValidPassword(copy_password) == false) {
    bool correct_password = false;

    do {
      std::cout << "Error, invalid password. Password must contain upper case, lower case, number, special charater and minimum size 8." << std::endl;
      std::cout << "Please try again: ";
      std::cin >> copy_password;
      correct_password = VerifyValidPassword(copy_password);
    } while (correct_password == false);
  }
  
  const std::string key = "KEY";  // LO QUE SEA
  const int shift = 3;            // LO QUE SEA

  const std::string encrypted_password = Encrypt(copy_password, key, shift);

  passwd << email << ", " << encrypted_password << std::endl;
}


/**
 * @brief Checks if a login is valid or not comparing the given password with the encrypted one (This function is on construction, it'll have to look if the user exists)
 * @param string email of the user
 * @param string given password
 * @param string name of the file that stores the encrypted passwords
 */
void VerifyLogIn(const std::string& email, const std::string& password, const std::string& password_file) {
  std::ifstream passwd(password_file);

  if (!passwd.is_open()) {
    // ERRROR
  }

  std::string line;
  const std::string key = "KEY";  // LO QUE SEA
  const int shift = 3;            // LO QUE SEA

  bool found = false;

  while (std::getline(passwd, line)) {
    std::stringstream ss(line);
    std::string file_email, encrypted_password;

    if (std::getline(ss, file_email, ',') && std::getline(ss, encrypted_password)) {
      if (!file_email.empty() && file_email.back() == ' ') {
        file_email.pop_back();
      }
      if (!encrypted_password.empty() && encrypted_password.front() == ' ') {
        encrypted_password.erase(0, 1);
      }

      if (file_email == email) {
        found = true;
        std::string decrypted_password = Decrypt(encrypted_password, key, shift);

        if (decrypted_password == password) {
          // CONTRASEÑA CORRECTA
        } else {
          // ERROR CONTRASEÑA INCORRECTA
        }
        break;
      }
    }
  }
  
  if (!found) {
    // NO ENCONTRADO
  }
}