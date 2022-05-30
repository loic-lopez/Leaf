//
// Created by LoicL on 24/12/2020.
//

#include "http/http_response.hpp"

namespace leaf::http::response
{
namespace MiscStrings
{

constexpr char name_value_separator[] = {':', ' '};
constexpr char crlf[]                 = {'\r', '\n'};

}// namespace MiscStrings

std::vector<boost::asio::const_buffer> HttpResponse::toBuffers()
{
  std::vector<boost::asio::const_buffer> buffers;

  buffers.emplace_back(status_strings::ToAsioBuffer(status));
  for (auto &header : headers)
  {
    HttpHeader &h = header;
    buffers.emplace_back(boost::asio::buffer(h.name));
    buffers.emplace_back(boost::asio::buffer(MiscStrings::name_value_separator));
    buffers.emplace_back(boost::asio::buffer(h.value));
    buffers.emplace_back(boost::asio::buffer(MiscStrings::crlf));
  }
  buffers.emplace_back(boost::asio::buffer(MiscStrings::crlf));
  buffers.emplace_back(boost::asio::buffer(content));
  return buffers;
}

HttpResponse HttpResponse::StockReply(HttpResponse::Status status)
{
  HttpResponse httpResponse;
  httpResponse.status  = status;
  httpResponse.content = stock_replies::StatusToStockReply(status);
  httpResponse.headers.resize(2);
  httpResponse.headers[0].name  = "Content-Length";
  httpResponse.headers[0].value = std::to_string(httpResponse.content.size());
  httpResponse.headers[1].name  = "Content-Type";
  httpResponse.headers[1].value = "text/html";
  return httpResponse;
}

}// namespace leaf::http::response