//
// Created by LoicL on 24/12/2020.
//

#include <fstream>
#include <utility>

#include "leaf_server/http/request_handler.hpp"

namespace leaf::server
{

RequestHandler::RequestHandler(std::string doc_root, mime_type::MimeTypes mimeTypes)
    : _documentRoot(std::move(doc_root)), _mimeTypes(std::move(mimeTypes))
{
}

void RequestHandler::handleRequest(const http::request::HttpRequest &httpRequest, http::response::HttpResponse &httpResponse)
{
  // Decode url to path.
  std::string request_path;
  if (!UrlDecode(httpRequest.uri, request_path))
  {
    httpResponse = http::response::HttpResponse::StockReply(http::response::HttpResponse::Status::bad_request);
    return;
  }

  // Request path must be absolute and not contain "..".
  if (request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos)
  {
    httpResponse = http::response::HttpResponse::StockReply(http::response::HttpResponse::Status::bad_request);
    return;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (request_path[request_path.size() - 1] == '/') { request_path += "index.html"; }

  // Determine the file extension.
  std::size_t last_slash_pos = request_path.find_last_of('/');
  std::size_t last_dot_pos   = request_path.find_last_of('.');
  std::string extension;
  if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) { extension = request_path.substr(last_dot_pos + 1); }

  // Open the file to send back.
  std::string full_path = _documentRoot + request_path;
  std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
  if (!is)
  {
    httpResponse = http::response::HttpResponse::StockReply(http::response::HttpResponse::Status::not_found);
    return;
  }

  // Fill out the reply to be sent to the client.
  httpResponse.status = http::response::HttpResponse::Status::ok;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
    httpResponse.content.append(buf, is.gcount());
  httpResponse.headers.resize(2);
  httpResponse.headers[0].name  = "Content-Length";
  httpResponse.headers[0].value = std::to_string(httpResponse.content.size());
  httpResponse.headers[1].name  = "Content-Type";
  httpResponse.headers[1].value = _mimeTypes.extensionToType(extension);
}

bool RequestHandler::UrlDecode(const std::string &in, std::string &out)
{
  out.clear();
  out.reserve(in.size());
  for (std::size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        std::istringstream is(in.substr(i + 1, 2));
        if (is >> std::hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else { return false; }
      }
      else { return false; }
    }
    else if (in[i] == '+') { out += ' '; }
    else { out += in[i]; }
  }
  return true;
}

}// namespace leaf::server
