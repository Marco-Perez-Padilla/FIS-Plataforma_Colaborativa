/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autores: Eduardo Javier Marichal de la Fuente, Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 21/04/2025

** Archivo menus.cc: Implementacion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**      23/04/2025 - Primera version funcional - Implementacion de login y mensajes
**      07/05/2025 - Mejoras para la implementacion de bases de datos de usuarios y mensajes
**/

#include <iostream>
#include <algorithm>
#include <limits>

#include "menus.h"
#include "login.h"
#include "exceptions.h"
#include "users.h"
#include "tareas.h"

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
            << "R. Recover password\n"
            << "Q. Quit\n"
            << "Choose: ";
  std::cin >> opt;
}

void LogInMenuAction(char &opt) {
  bool exit = false;
  do {
    clrscr();
    LogInMenuDescription(opt);
    switch (opt) {
      case 'L': {
        try {
          const User user = LogIn();
          // Añadimos el usuario si no estaba en la lista y apuntamos currentUser
          auto it = std::find_if(users.begin(), users.end(),
            [&](auto &u){ return u.getEmail() == user.getEmail(); });
          if (it == users.end()) {
            users.push_back(user);
            currentUser = &users.back();
          } else {
            currentUser = &*it;
          }
          // Recargamos la bandeja al entrar
          currentUser->clearInbox();
          auto mensajes = loadMessagesFromFile(currentUser->getEmail());
          for (auto &m : mensajes) currentUser->receiveMessage(m);

          std::cout << "Login successful. Press any key to continue...\n";
          pressanykey();
          return;
        } catch (const std::exception& error) {
          std::cerr << error.what() << std::endl;
          exit = true;
          break;
        }
      }
      case 'S': {
        try {
          User newU = Register();
          users.push_back(newU);
          currentUser = &users.back();
          std::cout << "Sign up successful. Press any key to continue...\n";
          pressanykey();
          return;
        } catch (const std::exception& error) {
          std::cerr << error.what() << std::endl;
          exit = true;
          break;
        }
      }
      case 'C': {
        bool changed = ChangePassword();
        if (!changed) exit = true;
        else {
          std::cout << "Password changed. Press any key...\n";
          pressanykey();
        }
        break;
      }
      case 'R': {
        bool recovered = RecoverPassword();
        if (!recovered) exit = true;
        break;
      }
      case 'Q':
        std::exit(0);
      default:
        std::cout << "Invalid option.\n";
        pressanykey();
    }
  } while (!exit);
  std::exit(1);
}

void MainMenuDescription(char &opt) {
  std::cout << "=== MAIN MENU ===\n"
            << "M. Send a message\n"
            << "B. View inbox\n"
            << "T. Create a task\n"
            << "S. Search a task\n"
            << "Q. Quit\n"
            << "Choose: ";
  std::cin >> opt;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

void MainMenuAction(char &opt) {
  do {
    clrscr();
    MainMenuDescription(opt);
    switch (opt) {
      case 'M': {
        std::string dest, text;
        std::cout << "Recipient email: ";
        std::getline(std::cin, dest);
      
        if (!userExists(dest)) {
          std::cout << "User not found.\n";
        } else {
          std::cout << "Message: ";
          std::getline(std::cin, text);
      
          // Persistimos en message_data_base.txt
          saveMessageToFile(
            currentUser->getEmail(),
            dest,
            text,
            std::chrono::system_clock::now(),
            false
          );
          std::cout << "Sent to " << dest << ".\n";
        }
        pressanykey();
        break;
      }
      case 'B': {
        // Refrescar bandeja
        currentUser->clearInbox();
        {
          auto mensajes = loadMessagesFromFile(currentUser->getEmail());
          for (auto &m : mensajes)
            currentUser->receiveMessage(m);
        }
        const auto &in = currentUser->getInbox();
        if (in.empty()) {
          std::cout << "Your inbox is empty.\n";
        } else {
          for (size_t i = 0; i < in.size(); ++i) {
            const auto &m = in[i];
            std::time_t t = std::chrono::system_clock::to_time_t(m.timestamp);
            std::cout << (m.read ? "[Read] " : "[New]  ")
                      << i+1 << ". From: " << m.sender
                      << " (" << std::ctime(&t) << ")\n" ;
          }
          std::cout << "Choose message number (0 to go back): ";
          size_t idx;
          std::cin >> idx;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          if (idx > 0 && idx <= in.size()) {
            auto &msg = const_cast<Message&>(in[idx-1]);
            std::cout << "\n--- Message ---\n" << msg.content << "\n";
            if (!msg.read) currentUser->markAsRead(idx-1);
          }
        }
        pressanykey();
        break;
      }
      case 'T': {
        if (checkRole(currentUser->getEmail()) != 1) {
          std::cerr << "Operation not allowed. Only available for teachers" << std::endl;
          pressanykey();
          break;
        }
        int various_students;
        std::cout << "Will the task be sent to various students? (0 = yes, 1 = no): ";
        std::cin >> various_students;
        bool various = true;
        if (various_students == 1) {
          various = false;
        } else if (various_students < 0 || various_students > 1) {
          break;
        }
        do { 
          std::string email;
          std::cout << "Introduce email of the student (Introduce 'Q' to finish): ";
          std::cin >> email;
          if (email == "Q") {
            std::cout << "Exit successful" << std::endl;
            break;
          }
          bool exists = userExists(email);
          if (exists == false) {
            std::cerr << "User not found" << std::endl;
            continue;
          }
          Task new_task = CreateTask(email);
          new_task.SaveTask();
          std::cout << "Task successfully created for " << email << std::endl;
          std::cout << std::endl;
        } while ((various_students != 0 || various_students != 1) && various == true);
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