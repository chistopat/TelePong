#include <iostream>

#include "server.h"

void RunServer(telepong::Server& server) {
  try {
    std::cout << "Server started!" << std::endl;
    server.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

auto main() -> int {
  auto server = telepong::Server(31337);
  RunServer(server);

  return 0;
}
