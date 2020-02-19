#pragma once
#include <curl/curl.h>
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>

class tinkoffApi {
private:
  std::string url;
  std::string urlSandbox;
  std::string result;
  std::string token;

public:
  tinkoffApi();
  tinkoffApi(const std::string &newToken);
  std::string GetUrl() const;
  std::string GetUrlSandbox() const;
  std::string Get(const std::string &token);
  void TestConnection(const bool &debug) const;
};
