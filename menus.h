/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Fundamentos de la Ingeniería del Software
** Curso: 2º
** Practica 6: Entrega de desarrollo ágil
** Autor: Marco Pérez Padilla, /////
** Correo: alu0101469348@ull.edu.es
** Fecha: 21/04/2025

** Archivo menus.h: Declaracion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**/

#ifndef MENUS_H
#define MENUS_H

void pressanykey();
void clrscr();
void LogInMenuDescription(char &option);
void LogInMenuAction(char &option);
void MainMenuDescription(char &option);
void MainMenuAction(char &opcion);
void AdministratorMenuDescription(char &option);
void AdministratorMenuAction(char &opcion);
void StudentMenuDescription(char &option);
void StudentMenuAction(char &opcion);
void TeacherMenuDescription(char &option);
void TeacherMenuAction(char &opcion);

#endif