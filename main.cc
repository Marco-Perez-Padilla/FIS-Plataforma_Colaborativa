#include "menus.h"

int main() {
  char opt;
  // 1) Login / sign-up hasta que currentUser != nullptr
  LogInMenuAction(opt);

  // 2) Menú principal: enviar mensajes / ver bandeja
  MainMenuAction(opt);

  return 0;
}