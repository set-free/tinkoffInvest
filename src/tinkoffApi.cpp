#include "tinkoffApi.hpp"

tinkoffApi::tinkoffApi()
    : url("https://api-invest.tinkoff.ru/openapi/"),
      urlSandbox("https://api-invest.tinkoff.ru/openapi/sandbox/"),
      strSnbReg("sandbox/register") {
  result = "value is not write";
  token = "token not set";
}

tinkoffApi::tinkoffApi(const std::string &newToken) : tinkoffApi() {
  token = newToken;
};

std::string tinkoffApi::GetUrl() const { return url; }

std::string tinkoffApi::GetUrlSandbox() const { return urlSandbox; }

void tinkoffApi::TestConnection(const bool &debug) const {
  try {
    std::ostringstream response;
    std::list<std::string> header;
    const std::string tokenHeader = "Authorization: Bearer " + token;
    if (debug) {
      spdlog::info("tokenHeader: " + tokenHeader);
      spdlog::info("Send post to register broker account");
    }
    std::string regJson = "{\"brokerAccountType\": \"Tinkoff\"}";
    int regJsonSize = static_cast<int>(regJson.size());
    header.push_back("User-Agent: curl/7.77.7");
    header.push_back("accept: application/json");
    header.push_back(tokenHeader);
    header.push_back("Content-Type: application/json");
    cURLpp::Options::Url reguestUrl;
    cURLpp::Options::PostFields postFields;
    curlpp::Cleanup MyCleanup;
    curlpp::Easy regReq;
    regReq.setOpt(new curlpp::options::Verbose(debug));
    regReq.setOpt(new curlpp::options::HttpHeader(header));
    regReq.setOpt<curlpp::options::Url>(urlSandbox + strSnbReg);
    regReq.setOpt(new curlpp::options::PostFields(regJson));
    regReq.setOpt(new curlpp::options::PostFieldSize(regJsonSize));
    regReq.setOpt(new curlpp::options::SslEngineDefault());
    //    regReq.setOpt(new curlpp::options::CustomRequest{"POST"});
    regReq.setOpt(new curlpp::options::WriteStream(&response));
    regReq.perform();
    regReq.getOpt(reguestUrl);
    regReq.getOpt(postFields);
    if (debug) {
      spdlog::info("Requested url: " + reguestUrl.getValue());
      spdlog::info("Post fields: " + postFields.getValue());
    }
    if (curlpp::infos::ResponseCode::get(regReq) == 200) {
      auto resultJson = response.str();
      // TODO: Add parse JSON: "status":"Ok"
      if (!resultJson.empty()) {
        spdlog::info(resultJson);
      }
      if (debug) {
        spdlog::info("Send get info about orders");
      }
      response.str("");
      resultJson.clear();
      header.clear();
      header.push_back("User-Agent: curl/7.77.7");
      header.push_back("accept: application/json");
      header.push_back(tokenHeader);
      curlpp::Easy takeInfReq;
      takeInfReq.setOpt<curlpp::options::Url>(urlSandbox + "orders");
      takeInfReq.setOpt(new curlpp::options::Verbose(debug));
      takeInfReq.setOpt(new curlpp::options::WriteStream(&response));
      takeInfReq.setOpt(new curlpp::options::HttpHeader(header));
      takeInfReq.perform();
      if (curlpp::infos::ResponseCode::get(takeInfReq) == 200) {
        resultJson = response.str();
        if (!resultJson.empty()) {
          spdlog::info(resultJson);
        }
      } else {
        spdlog::error(
            "Response code: " +
            std::to_string(curlpp::infos::ResponseCode::get(takeInfReq)));
        std::exit(EXIT_FAILURE);
      }
    } else {
      spdlog::error("Response code: " +
                    std::to_string(curlpp::infos::ResponseCode::get(regReq)));
      std::exit(EXIT_FAILURE);
    }
  } catch (curlpp::RuntimeError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  } catch (curlpp::LogicError &e) {
    spdlog::error(e.what());
    std::exit(EXIT_FAILURE);
  }
}
