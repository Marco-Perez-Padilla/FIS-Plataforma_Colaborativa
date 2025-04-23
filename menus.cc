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

** Archivo menus.h: Declaracion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**/

#include <iostream>
#include <algorithm>
#include <limits>

#include "menus.h"
#include "login.h"

std::vector<User> users;
User* currentUser = nullptr;

// Including libreries for compatibility among operative systems
#ifdef _WIN32
  #include <conio.h>  // _getch() for pressanykey
  #define CLEAR "cls" // Macro for clrscr in Windows
#else
  #define CLEAR "clear" // Macro for clrscr in Linux
#endif

/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  #ifdef _WIN32
    _getch(); // Windows
  #else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Linux
    std::cin.get(); 
  #endif
}

/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system(CLEAR);
}

void LogInMenuDescription(char &opt) {
  std::cout << "=== LOGIN MENU ===\n"
            << "L. Log in\n"
            << "S. Sign up\n"
            << "C. Change password\n"
            << "Q. Quit\n"
            << "Choose: ";
  std::cin >> opt;
}

void LogInMenuAction(char &opt) {
  do {
    clrscr();
    LogInMenuDescription(opt);
    switch (opt) {
      case 'L': {
        std::string email, password;
        std::cout << "Email: ";
        std::cin >> email;
        std::cout << "Password: ";
        std::cin >> password;
        std::string pwd_file = "passwords.txt";
        User temp(email, email.substr(0, email.find('@')));
        VerifyLogIn(temp, password, pwd_file);
        // si llega aquí, login OK
        auto it = std::find_if(users.begin(), users.end(),
          [&](auto &u){ return u.getEmail() == email; });
        if (it == users.end()) {
          users.push_back(temp);
          currentUser = &users.back();
        } else {
          currentUser = &*it;
        }
        std::cout << "Login successful. Press any key to continue…\n";
        pressanykey();
        return;
      }
      case 'S': {
        std::string name, email, password;
        std::cout << "Name: ";
        std::cin >> name;
        std::cout << "Email: ";
        std::cin >> email;
        std::cout << "Password: ";
        std::cin >> password;
        std::string pwd_file = "passwords.txt";
        User newU(email, name);
        SignUpUser(newU, password, pwd_file);
        users.push_back(newU);
        currentUser = &users.back();
        std::cout << "Sign up successful. Press any key to continue…\n";
        pressanykey();
        return;
      }
      case 'C':
        ChangePassword();
        std::cout << "Password changed. Press any key…\n";
        pressanykey();
        break;
      case 'Q':
        std::exit(0);
      default:
        std::cout << "Invalid option.\n";
        pressanykey();
    }
  } while (true);
}

void MainMenuDescription(char &opt) {
  std::cout << "=== MAIN MENU ===\n"
            << "M. Send a message\n"
            << "B. View inbox\n"
            << "Q. Quit\n"
            << "Choose: ";
  std::cin >> opt;
}

void MainMenuAction(char &opt) {
  do {
    clrscr();
    MainMenuDescription(opt);
    switch (opt) {
      case 'M': {
        std::string dest, text;
        std::cout << "Recipient email: ";
        std::cin >> dest;
        std::cout << "Message: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::getline(std::cin, text);
        auto it = std::find_if(users.begin(), users.end(),
          [&](auto &u){ return u.getEmail() == dest; });
        if (it != users.end()) {
          currentUser->sendMessage(*it, text);
          std::cout << "Sent to " << it->getUsername() << ".\n";
        } else {
          std::cout << "User not found.\n";
        }
        pressanykey();
        break;
      }
      case 'B': {
        const auto &in = currentUser->getInbox();
        if (in.empty()) {
          std::cout << "Your inbox is empty.\n";
        } else {
          for (size_t i = 0; i < in.size(); ++i) {
            auto &m = in[i];
            std::cout << (m.read ? "[Read] " : "[New]  ")
                      << m.sender << ": " << m.content << "\n";
            currentUser->markAsRead(i);
          }
        }
        pressanykey();
        break;
      }
      case 'Q':
        std::exit(0);
      default:
        std::cout << "Invalid option.\n";
        pressanykey();
    }
  } while (true);
}