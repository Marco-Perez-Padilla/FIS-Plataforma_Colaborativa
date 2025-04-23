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
#include <limits>

#include "menus.h"
#include "login.h"

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



/**
* @brief Start menu to choose an option of the following
* @param char option to be used
*/
void LogInMenuDescription (char &opcion) {
  std::cout << "L. [L]og into the plattform" << std::endl;     
  std::cout << "S. [S]ign up" << std::endl;
  std::cout << "C. [C]hange password" << std::endl;        
  std::cout << "q. [q]uit program" << std::endl;
  std::cout << "Introduce the action to execute  > ";
  std::cin >> opcion;
};
 

/**
 * @brief Function that uses the description of the login menu and calls its functions
 * @param char chosen option 
 */
void LogInMenuAction (char &opcion) {
  char option;
  do {
    clrscr();
    LogInMenuDescription(option);

    switch (option) {
      case 'L':
        LogIn(); // Hacer try-catch aqui
        std::cout << "Log in successful. Press any key to continue" << std::endl;
        pressanykey();
        // Mandar a otro menú o algo
        MainMenuAction(option);
      break;

      case 'S':
        Register(); // Comprobar si ya estaba registrado antes
        std::cout << "Sign up successful. Press any key to continue" << std::endl;
        pressanykey();
      break;

      case 'C':
        ChangePassword();
        std::cout << "Log in successful. Press any key to continue" << std::endl;
        pressanykey();
      break;
    }
  } while (option != 'q');
}


/**
* @brief Start menu to choose an option of the following
* @param char option to be used
*/
void MainMenuDescription (char &opcion) {
 std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
 std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
 std::cout << "o. Enter [o]rdenation mode" << std::endl;        
 std::cout << "q. [q]uit program" << std::endl;
 std::cout << "Introduce the action to execute  > ";
 std::cin >> opcion;
};


/**
 * @brief Function that uses the description of the main menu and calls its functions
 * @param char chosen option 
 */
void MainMenuAction (char &opcion) {
  char option;
  do {
    MainMenuDescription(option);

    switch (option) {
      case 'a':

      break;

      case 'b':

      break;

      case 'c':

      break;

      //
    }
  } while (option != 'q');
}


/**
* @brief Menu only accessible if the user is an Administrator. Shows the options to administrate the plattform
* @param char option to be used
*/
void AdministratorMenuDescription (char &opcion) {
  std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
  std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
  std::cout << "o. Enter [o]rdenation mode" << std::endl;        
  std::cout << "q. [q]uit program" << std::endl;
  std::cout << "Introduce the action to execute  > ";
  std::cin >> opcion;
};


/**
 * @brief Function that uses the description of the administator menu and calls its functions
 * @param char chosen option 
 */
void AdministratorMenuAction (char &opcion) {
  char option;
  do {
    AdministratorMenuDescription(option);

    switch (option) {
      case 'a':

      break;

      case 'b':

      break;

      case 'c':

      break;

      //
    }
  } while (option != 'q');
}


/**
* @brief Menu  accessible if the user is a Student or an Administrator. Shows the options the student can do in the plattform.
* @param char option to be used
*/
void StudentMenuDescription (char &opcion) {
  std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
  std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
  std::cout << "o. Enter [o]rdenation mode" << std::endl;        
  std::cout << "q. [q]uit program" << std::endl;
  std::cout << "Introduce the action to execute  > ";
  std::cin >> opcion;
};


/**
 * @brief Function that uses the description of the student menu and calls its functions
 * @param char chosen option 
 */
void StudentMenuAction (char &opcion) {
  char option;
  do {
    StudentMenuDescription(option);

    switch (option) {
      case 'a':

      break;

      case 'b':

      break;

      case 'c':

      break;

      //
    }
  } while (option != 'q');
}



/**
* @brief Menu  accessible if the user is a Teacher or an Administrator. Shows the options the teacher can do in the plattform.
* @param char option to be used
*/
void TeacherMenuDescription (char &opcion) {
  std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
  std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
  std::cout << "o. Enter [o]rdenation mode" << std::endl;        
  std::cout << "q. [q]uit program" << std::endl;
  std::cout << "Introduce the action to execute  > ";
  std::cin >> opcion;
};


/**
 * @brief Function that uses the description of the teacher menu and calls its functions
 * @param char chosen option 
 */
void TeacherMenuAction (char &opcion) {
  char option;
  do {
    TeacherMenuDescription(option);

    switch (option) {
      case 'a':

      break;

      case 'b':

      break;

      case 'c':

      break;

      //
    }
  } while (option != 'q');
}