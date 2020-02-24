#include "http.hpp"

HTTP::HTTP() {}
//    : url("https://api-invest.tinkoff.ru/openapi/"),
//      urlSandbox("https://api-invest.tinkoff.ru/openapi/sandbox/") {}

HTTP::HTTP(const std::string &newToken) : HTTP() {
  token = newToken;
  tokenHeader = "Authorization: Bearer " + token;
};

std::string HTTP::Get(const std::string &getUrl, const bool &debug) const {
  try {
    std::ostringstream response;
    std::list<std::string> header;
    if (debug) {
      spdlog::info("tokenHeader: " + tokenHeader);
      spdlog::info("Sending GET request to: " + getUrl);
    }
    header.push_back("User-Agent: curl/7.77.7");
    header.push_back("Content-Type: application/json");
    header.push_back(tokenHeader);
    cURLpp::Options::Url url;
    cURLpp::Options::PostFields postFields;
    curlpp::Cleanup MyCleanup;
    curlpp::Easy request;
    request.setOpt(new curlpp::options::Verbose(debug));
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt<curlpp::options::Url>(getUrl);
    request.setOpt(new curlpp::options::SslEngineDefault());
    request.setOpt(new curlpp::options::WriteStream(&response));
    // url.setOpt(new curlpp::options::CustomRequest{"GET"});
    request.perform();
    request.getOpt(url);
    if (debug) {
      spdlog::info("Requested url: " + url.getValue());
    }
    if (curlpp::infos::ResponseCode::get(request) == 200) {
      std::string resultJson = response.str();
      // TODO: Add parse JSON: "status":"Ok"
      if (!resultJson.empty()) {
        if (debug) {
          spdlog::info("Response data:" + resultJson + "\n");
        }
        return resultJson;
      }
    } else {
      spdlog::error("Response data is empty");
      spdlog::error("Response code: " +
                    std::to_string(curlpp::infos::ResponseCode::get(request)));
      std::exit(EXIT_FAILURE);
    }
  } catch (curlpp::RuntimeError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  } catch (curlpp::LogicError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  }
  return "EXIT_FAILURE";
}

std::string HTTP::Post(const std::string &getUrl, const bool &debug,
                       const std::string &postData) const {
  try {
    std::ostringstream response;
    std::list<std::string> header;
    if (debug) {
      spdlog::info("Token Header: " + tokenHeader);
      spdlog::info("Sending POST: " + getUrl);
      spdlog::info("Sending POST DATA: " + postData);
    }
    int postDataSize = static_cast<int>(postData.size());
    header.push_back("User-Agent: curl/7.77.7");
    header.push_back("accept: application/json");
    header.push_back(tokenHeader);
    header.push_back("Content-Type: application/json");
    cURLpp::Options::Url url;
    cURLpp::Options::PostFields postFields;
    curlpp::Cleanup MyCleanup;
    curlpp::Easy request;
    request.setOpt(new curlpp::options::Verbose(debug));
    request.setOpt(new curlpp::options::HttpHeader(header));
    request.setOpt<curlpp::options::Url>(getUrl);
    request.setOpt(new curlpp::options::PostFields(postData));
    request.setOpt(new curlpp::options::PostFieldSize(postDataSize));
    request.setOpt(new curlpp::options::SslEngineDefault());
    request.setOpt(new curlpp::options::WriteStream(&response));
    // request.setOpt(new curlpp::options::CustomRequest{"POST"});
    request.perform();
    request.getOpt(url);
    request.getOpt(postFields);
    if (debug) {
      spdlog::info("Requested url: " + url.getValue());
      spdlog::info("Posted data: " + postFields.getValue());
    }
    if (curlpp::infos::ResponseCode::get(request) == 200) {
      auto resultJson = response.str();
      // TODO: Add parse JSON: "status":"Ok"
      if (!resultJson.empty()) {
        if (debug) {
          spdlog::info("Response data:" + resultJson + "\n");
        }
        return resultJson;
      }
    } else {
      spdlog::error("Response data is empty");
      spdlog::error("Response code: " +
                    std::to_string(curlpp::infos::ResponseCode::get(request)));
      std::exit(EXIT_FAILURE);
    }
  } catch (curlpp::RuntimeError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  } catch (curlpp::LogicError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  }
  return "EXIT_FAILURE";
}
