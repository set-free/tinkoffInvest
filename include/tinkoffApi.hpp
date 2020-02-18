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
  std::string urlSandbox;
  std::string url;
  std::string result;

public:
  tinkoffApi();
  std::string GetUrl() const;
  std::string GetUrlSandbox() const;
  std::string Get(const std::string &token);
  void TestConnection(const std::string &token, const bool &debug) const;
};
