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
void MainMenu (char &opcion) {
 std::cout << "i. [i]nsert new NIF, number with 8 digits" << std::endl;     
 std::cout << "s. [s]earch a specified NIF in the table hash" << std::endl;
 std::cout << "o. Enter [o]rdenation mode" << std::endl;        
 std::cout << "q. [q]uit program" << std::endl;
 std::cout << "Introduce the action to execute  > ";
 std::cin >> opcion;
};
