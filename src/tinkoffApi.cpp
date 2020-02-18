#include "tinkoffApi.hpp"

tinkoffApi::tinkoffApi() {
  url = "https://api-invest.tinkoff.ru/openapi/";
  urlSandbox = "https://api-invest.tinkoff.ru/openapi/sandbox/orders";
  result = "value is not write";
}

std::string tinkoffApi::GetUrl() const { return url; }
std::string tinkoffApi::GetUrlSandbox() const { return urlSandbox; }
std::string tinkoffApi::Get(const std::string &token) {
  try {
    std::ostringstream response;
    std::list<std::string> header;
    std::string tokenHeader = "Authorization: Bearer " + token;
    std::cout << "tokenHeader: " << tokenHeader << std::endl;
    header.push_back("Content-Type: application/json");
    header.push_back(tokenHeader);
    curlpp::Cleanup MyCleanup;
    curlpp::Easy myRequest;
    myRequest.setOpt<curlpp::options::Url>(urlSandbox);
    myRequest.setOpt(new curlpp::options::Verbose(false));
    myRequest.setOpt(new curlpp::options::WriteStream(&response));
    myRequest.setOpt(new curlpp::options::HttpHeader(header));
    myRequest.perform();
    result = response.str();
    cURLpp::Options::Url myUrl;
    myRequest.getOpt(myUrl);
  } catch (curlpp::RuntimeError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  } catch (curlpp::LogicError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  }
  return result;
}

void tinkoffApi::TestConnection(const std::string &token,
                                const bool &debug) const {
  try {
    std::ostringstream response;
    std::list<std::string> header;
    const std::string tokenHeader = "Authorization: Bearer " + token;
    spdlog::info("tokenHeader: " + tokenHeader);
    header.push_back("Content-Type: application/json");
    header.push_back(tokenHeader);
    curlpp::Cleanup MyCleanup;
    curlpp::Easy myRequest;
    myRequest.setOpt<curlpp::options::Url>(urlSandbox);
    myRequest.setOpt(new curlpp::options::Verbose(debug));
    myRequest.setOpt(new curlpp::options::WriteStream(&response));
    myRequest.setOpt(new curlpp::options::HttpHeader(header));
    myRequest.perform();
    if (curlpp::infos::ResponseCode::get(myRequest) >= 500) {
      spdlog::error(
          "Response code: " +
          std::to_string(curlpp::infos::ResponseCode::get(myRequest)));
      std::exit(EXIT_FAILURE);
    }
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
    std::exit(EXIT_FAILURE);
  } catch (curlpp::LogicError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  }
}
