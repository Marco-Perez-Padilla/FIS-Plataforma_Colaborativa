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
**      23/04/2025 - Adicion funciones de recuperacion de contraseña y excepciones
**/

#ifndef LOGIN_H
#define LOGIN_H

#include <string>

#include "users.h"

std::string KeyCypher(const std::string& password, const std::string& key);
std::string CaesarCypher(const std::string& text, int shift);
std::string Encrypt(const std::string& password, const std::string& key, int shift);
std::string Decrypt(const std::string& encrypted, const std::string& key, int shift);
bool CheckEmail(const std::string& email);
bool VerifyValidPassword(const std::string& password);
bool isSignedUp(const User& user, const std::string& password_file);
void SignUpUser(const User& user, const std::string& password, std::string& password_file, const std::string& answer);
bool VerifyLogIn(const User& user, const std::string& password, const std::string& password_file);
const std::string VerifyAnswer(const User& user, const std::string& answer, const std::string& password_file);
const User Register();
const User LogIn();
bool ChangePassword();
bool RecoverPassword();
void ReplacePassword(const User& user, const std::string& password, const std::string& password_file);


#endif