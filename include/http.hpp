#pragma once

#include <curl/curl.h>
#include <spdlog/spdlog.h>

#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <iostream>
#include <sstream>
#include <string>

class HTTP {
 private:
  std::string token;
  std::string tokenHeader;

 public:
  HTTP();
  HTTP(const std::string &newToken);
  std::string Get(const std::string &getUrl, const bool &debug) const;
  std::string Post(const std::string &getUrl, const bool &debug,
                   const std::string &postData) const;
};
