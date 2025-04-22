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

** Archivo login.h: Declaracion de las funciones de menus.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/04/2025 - Creacion (primera version) del codigo
**/


#include <string>

std::string KeyCypher(const std::string& password, const std::string& key);
std::string CaesarCypher(const std::string& text, int shift);
std::string Encrypt(const std::string& password, const std::string& key, int shift);
std::string Decrypt(const std::string& encrypted, const std::string& key, int shift);
bool VerifyValidPassword(const std::string& password);
void SignUpUser(const std::string& email, const std::string& password, std::string& password_file);
void VerifyLogIn(const std::string& email, const std::string& password, const std::string& password_file);
void Register();
void LogIn();
void ChangePassword() ;