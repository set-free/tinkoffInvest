#include <iostream>

#include "tinkoff.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Need enter TokeApi" << std::endl;
    return 0;
  }
  bool debug = false;
  if (argc > 2 and std::string(argv[2]) == "debug") {
    std::cout << "Debug mode: ON" << std::endl;
    debug = true;
  }
  const std::string token = argv[1];
  Tinkoff connect(token, debug);
  connect.Register();
  connect.Orders();
  return 0;
}
