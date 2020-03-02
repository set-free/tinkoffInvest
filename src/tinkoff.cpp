#include "tinkoff.hpp"

Tinkoff::Tinkoff()
    : urlTest("https://api-invest.tinkoff.ru/openapi/sandbox/"),
      urlProd("https://api-invest.tinkoff.ru/openapi/") {};

Tinkoff::Tinkoff(const std::string &newToken, const bool &_debug) : Tinkoff() {
  token = newToken;
  debug = _debug;
};

std::string Tinkoff::Register() const {
  const std::string header = "{\"brokerAccountType\": \"Tinkoff\"}";
  HTTP http(token);
  http.Post(urlTest + "sandbox/register", debug, header);
  return "";
}

std::string Tinkoff::Orders() const {
  HTTP http(token);
  http.Get(urlTest + "orders", debug);
  //  json ResJSON = json::parse(http.Get(urlTest + "orders", debug));
  //  std::cout << "ResJSON: " << ResJSON["status"] << "\n";
  return "";
}
