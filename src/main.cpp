#include "tinkoffApi.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Need enter TokeApi" << std::endl;
    return 0;
  }
  bool debug = false;
  if (argc > 2 and std::string(argv[2]) == "debug") {
    spdlog::info("Enable debug mode");
    debug = true;
  }
  const std::string token = argv[1];
  const std::string getUrl =
      "https://api-invest.tinkoff.ru/openapi/sandbox/orders";
  tinkoffApi tinkoff;
  tinkoff.TestConnection(token, debug);
  //  auto httpContent = HTTP.GetUrl(getUrl, token);
  return 0;
}
