#include "application/bootstrap/AppContext.h"
#include "application/ui/ConsoleUI.h"

int main() {
   ConsoleUI::intro();

   auto app = AppContext::build();
   app->run();

   ConsoleUI::outro();
   return 0;
}
