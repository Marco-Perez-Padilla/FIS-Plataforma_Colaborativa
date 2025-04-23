/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Marco Pérez Padilla, 
** Correo: alu0101469348@ull.edu.es
** Fecha: 21/04/2025

** Archivo login.cc: Implementacion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**      23/04/2025 - Adicion funciones de recuperacion de contraseña y excepciones
**/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

#include "menus.h"
#include "login.h"
#include "users.h"
#include "exceptions.h"


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
 * @brief Verifies if a given email is valid (but not if it exists)
 * @param string email to be checked
 * @return true if the format is valid, false otherwise
 */
bool CheckEmail(const std::string& email) {
  std::regex pattern(R"(^(\d{10}@ull\.edu\.es|[a-zA-Z0-9._%+-]+@(ull\.es|gmail\.com))$)");
  return std::regex_match(email, pattern);
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
 * @brief Verifies is a user is already signed up or not
 * @param User to be verified
 * @param string name of the password file
 * @return true if registered, false otherwise
 */
bool isSignedUp(const User& user, const std::string& password_file) {
  std::ifstream passwd(password_file);

  if (!passwd.is_open()) {
    throw OpenFileException(password_file);
  }

  std::string line;

  bool found = false;

  while (std::getline(passwd, line)) {
    std::stringstream ss(line);
    std::string file_email, encrypted_password;

    if (std::getline(ss, file_email, ',') && std::getline(ss, encrypted_password)) {
      if (file_email == user.getEmail()) { 
        found = true;
        break;
      }
    }
  }
  
  if (!found) {
    return false;
  }

  return true;
}


/**
 * @brief Sign ups a user with email and password 
 * @param User user to be signed up 
 * @param string password of the user
 * @param string recovering password answer
 * @param string name of the file that stores the encrypted passwords
 * @param string name of the data base file
 */
void SignUpUser(const User& user, const std::string& password, const std::string& answer, std::string& password_file, std::string& data_base) {  
  std::string copy_password = password;     
  std::string copy_answer = answer;                                                         
  std::ofstream passwd(password_file, std::ios::app);
  std::ofstream db (data_base, std::ios::app);

  if (!passwd.is_open()) {
    throw OpenFileException(password_file);
  } 

  if (isSignedUp(user, password_file)) {
    throw AlreadyRegisteredException();
  }

  if (!db.is_open()) {
    throw OpenFileException(data_base);
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
  
  const std::string key = "CrEdITs";  
  const int shift = 6;            

  const std::string encrypted_password = Encrypt(copy_password, key, shift);
  const std::string encrypted_answer = Encrypt(copy_answer, key, shift);

  passwd << user.getEmail() << ", " << encrypted_password << ", " << encrypted_answer << std::endl; 
}


/**
 * @brief Checks if a login is valid or not comparing the given password with the encrypted one 
 * @param User user to be logged in 
 * @param string given password
 * @param string name of the file that stores the encrypted passwords
 * @return true if the user can be logged in, false otherwise
 */
bool VerifyLogIn(const User& user, const std::string& password, const std::string& password_file) {
  std::ifstream passwd(password_file);

  if (!passwd.is_open()) {
    throw OpenFileException(password_file);
  }

  if (!isSignedUp(user, password_file)) {
    throw NonRegisteredException();
  }

  std::string line;
  const std::string key = "CrEdITs";  
  const int shift = 6;            

  bool found = false;

  while (std::getline(passwd, line)) {
    std::stringstream ss(line);
    std::string file_email, encrypted_password, encrypted_answer;

    if (std::getline(ss, file_email, ',') && std::getline(ss, encrypted_password, ',') && std::getline(ss, encrypted_answer)) {
      if (!file_email.empty() && file_email.back() == ' ') {
        file_email.pop_back();
      }
      if (!encrypted_password.empty() && encrypted_password.front() == ' ') {
        encrypted_password.erase(0, 1);
      }

      if (file_email == user.getEmail()) { 
        found = true;
        std::string decrypted_password = Decrypt(encrypted_password, key, shift);

        if (decrypted_password == password) {
          return true;
        } else {
          throw WrongPasswordException();
        }
      }
    }
  }
}


/**
 * @brief Verifies is the answer to the recover password question is valid or not
 * @param string given answer to the question
 * @param string name of the file that stores the encrypted passwords and answers
 * @return string password of the user if the answer was correct
 */
const std::string& VerifyAnswer(const User& user, const std::string& answer, const std::string& password_file) {
  std::ifstream passwd(password_file);

  if (!passwd.is_open()) {
    throw OpenFileException(password_file);
  }

  if (!isSignedUp(user, password_file)) {
    throw NonRegisteredException();
  }

  std::string line;
  const std::string key = "CrEdITs";  
  const int shift = 6;            

  bool found = false;

  while (std::getline(passwd, line)) {
    std::stringstream ss(line);
    std::string file_email, encrypted_password, encrypted_answer;

    if (std::getline(ss, file_email, ',') && std::getline(ss, encrypted_password, ',') && std::getline(ss, encrypted_answer)) {
      if (!file_email.empty() && file_email.back() == ' ') {
        file_email.pop_back();
      }
      if (!encrypted_password.empty() && encrypted_password.front() == ' ') {
        encrypted_password.erase(0, 1);
      }

      if (file_email == user.getEmail()) { 
        found = true;
        std::string decrypted_answer = Decrypt(encrypted_answer, key, shift);

        if (decrypted_answer == answer) {
          const std::string decrypted_password = Decrypt(encrypted_password, key, shift);
          return decrypted_password;
        } else {
          throw WrongAnswerException();
        }
      }
    }
  }
}


/**
 * @brief Replaces a password for a new one
 * @param User user whose password will be changed
 * @param string new password
 * @param string name of the file that stores the encrypted passwords and answers
 */
void ReplacePassword(const User& user, const std::string& new_password, const std::string& password_file) {
  std::ifstream infile(password_file);
  std::ofstream outfile("temp.txt");
  const std::string key = "CrEdITs";
  const int shift = 6;

  std::ifstream passwd(password_file);

  if (!infile.is_open()) {
    throw OpenFileException(password_file);
  }

  std::string line;
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string file_email, encrypted, encrypted_answer;

    if (std::getline(ss, file_email, ',') && std::getline(ss, encrypted, ',') && std::getline(ss, encrypted_answer, ',')) {
      if (!file_email.empty() && file_email.back() == ' ') {
        file_email.pop_back();
      }
      if (file_email == user.getEmail()) {
        std::string encrypted_password = Encrypt(new_password, key, shift);
        outfile << file_email << ", " << encrypted_password << ", " << encrypted_answer << std::endl;
      } else {
        outfile << line << std::endl;
      }
    }
  }

  infile.close();
  outfile.close();

  std::remove(password_file.c_str());
  std::rename("temp.txt", password_file.c_str());
}


/**
 * @brief Registers a user, storaging it on the data base and password file
 * @return true if the register process was correct, false otherwise
 */
bool Register() {
  std::string name;
  std::string email;
  std::string password;
  std::string answer;
  std::string password_file = "password_manager.txt"; // Creo que es mejor ponerlo en un #define o en una macro
  std::string data_base = "data_base.txt";

  std::cout << "Enter name: ";
  std::cin >> name;
  std::cout << "Enter email: "; // Puedo hacer funcion de verificacion de que sea un email, al menos con @ull.edu.es, @ull.es y @gmail.com
  std::cin >> email;
  std::cout << "Enter password: ";

  User user(email, name);

  std::cout << "Answer to the next security question (question backup)" << std::endl;
  std::cout << "What's the name of your first pet? : ";
  std::cin >> answer;

  try {
    SignUpUser(user, password, answer, password_file, data_base);
  } catch (const OpenFileException& error) {
    std::cerr << error.what() << std::endl;
    return false;
  } catch (const AlreadyRegisteredException& error) {
    std::cerr << error.what() << std::endl;
    return false;
  }
  return true;
}


/**
 * @brief Allows or denies the login
 * @return User logged in
 */
const User LogIn() {
  std::string email;
  std::string name;
  std::string password;
  std::string password_file = "password_manager.txt"; // Creo que es mejor ponerlo en un #define o en una macro

  std::cout << "Enter email: "; // Puedo hacer funcion de verificacion de que sea un email, al menos con @ull.edu.es, @ull.es y @gmail.com
  std::cin >> email;
  std::cout << "Enter password: ";
  std::cin >> password;
  
  User user(email, name);
  VerifyLogIn(user, password, password_file); 
  return user;
}


/**
 * @brief Allows a user to recover the password
 * @return true if the password could be recovered, false otherwise
 */
bool RecoverPassword() {
  std::string email;
  std::string name;
  std::string password;
  std::string answer;
  std::string password_file = "nombre_archivo_contraseña.txt"; // Creo que es mejor ponerlo en un #define o en una macro

  std::cout << "Enter email: "; // Puedo hacer funcion de verificacion de que sea un email, al menos con @ull.edu.es, @ull.es y @gmail.com
  std::cin >> email;

  User user(email, name);

  std::cout << "What's the name of your first pet? : ";
  std::cin >> answer;

  try {
  const std::string password = VerifyAnswer(user, answer, password_file);
  } catch (const OpenFileException& error) {
    std::cerr << error.what() << std::endl;
    return false;
  } catch (const WrongAnswerException& error) {
    std::cerr << error.what() << std::endl;
    return false;
  }

  std::cout << "The password is: " << password << std::endl;
  return true;
}


/**
 * @brief Allows the change of a password
 * @return true if the password could be changed, false otherwise
 */
bool ChangePassword() {  
  std::string email;
  std::string old_password;
  std::string new_password;
  std::string name;
  std::string password_file = "nombre_archivo_contraseña.txt"; // Creo que es mejor ponerlo en un #define o en una macro

  std::cout << "Enter email: "; // Puedo hacer funcion de verificacion de que sea un email, al menos con @ull.edu.es, @ull.es y @gmail.com
  std::cin >> email;
  std::cout << "Enter old password: ";
  std::cin >> old_password;
  User user(email, name);

  VerifyLogIn(user, old_password, password_file);
  std::cout << "Enter new password: ";
  std::cin >> new_password;

  try {
    ReplacePassword(user, new_password, password_file);
  } catch (const OpenFileException& error) {
    std::cerr << error.what() << std::endl;
    return false;
  }
  return true;
}