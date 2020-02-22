#include <iostream>
#include <nlohmann/json.hpp>

#include "http.hpp"

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
  const std::string regHeader = "{\"brokerAccountType\": \"Tinkoff\"}";
  const std::string urlProd = "https://api-invest.tinkoff.ru/openapi/";
  const std::string urlTest = "https://api-invest.tinkoff.ru/openapi/sandbox/";
  HTTP tinkoff(token);
  tinkoff.Post(urlTest + "sandbox/register", debug, regHeader);
  tinkoff.Get(urlTest + "orders", debug);
  //  using json = nlohmann::json;
  //  json resultGet = json::parse(tinkoff.Get(
  //      "https://api-invest.tinkoff.ru/openapi/sandbox/orders", debug));
  //  std::cout << "resultGet: " << resultGet["status"] << "\n";
  return 0;
}
