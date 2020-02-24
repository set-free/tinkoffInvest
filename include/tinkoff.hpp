#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "http.hpp"

class Tinkoff {
  using json = nlohmann::json;

 private:
  const std::string urlTest;
  const std::string urlProd;
  std::string token;
  bool debug;

 public:
  Tinkoff();
  Tinkoff(const std::string &newToken, const bool &debug);
  std::string Register() const;
  std::string Orders() const;
};
