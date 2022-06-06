//
// Created by LoicL on 24/12/2020.
//

#include <filesystem>
#include <fstream>
#include <iterator>
#include <utility>

#include "leaf_server/http/request_handler.hpp"

namespace leaf::server
{

RequestHandler::RequestHandler(std::string docRoot, mime_type::MimeTypes mimeTypes)
    : _documentRoot(std::move(docRoot)), _mimeTypes(std::move(mimeTypes))
{
}

void RequestHandler::handleRequest(const http::request::HttpRequest &httpRequest, http::response::HttpResponse &httpResponse) const
{
  // Decode url to path.
  std::string requestPath;
  if (!CheckForBadRequest(httpRequest, requestPath))
  {
    httpResponse = http::response::HttpResponse::StockReply(http::response::HttpResponse::Status::bad_request);
    return;
  }

  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (requestPath[requestPath.size() - 1] == '/') { requestPath += "index.html"; }

  // Determine the file extension.
  const std::size_t lastSlashPos = requestPath.find_last_of('/');
  const std::size_t lastDotPos   = requestPath.find_last_of('.');
  std::string extension;
  if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos) { extension = requestPath.substr(lastDotPos + 1); }

  // Open the file to send back.
  const std::string fullPath = _documentRoot + requestPath;
  std::ifstream is(fullPath, std::ios::in | std::ios::binary);
  if (!is)
  {
    httpResponse = http::response::HttpResponse::StockReply(http::response::HttpResponse::Status::not_found);
    return;
  }

  // Fill out the reply to be sent to the client.
  httpResponse.status = http::response::HttpResponse::Status::ok;

  const std::uintmax_t fileSize = std::filesystem::file_size(std::filesystem::path(fullPath));

  // read the file
  httpResponse.content = GetFileContent(is, fileSize);
  httpResponse.headers.resize(2);
  httpResponse.headers[0].name  = "Content-Length";
  httpResponse.headers[0].value = std::to_string(httpResponse.content.size());
  httpResponse.headers[1].name  = "Content-Type";
  httpResponse.headers[1].value = _mimeTypes.extensionToType(extension);
}

std::string RequestHandler::GetFileContent(std::ifstream &is, const std::uintmax_t fileSize)
{
  std::vector<char> bytes(fileSize);
  is.read(bytes.data(), static_cast<std::streamsize>(fileSize));

  return std::string(bytes.data(), fileSize);
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

bool RequestHandler::CheckForBadRequest(const http::request::HttpRequest &httpRequest, std::string &requestPath)
{
  const bool isUrlDecoded = UrlDecode(httpRequest.uri, requestPath);
  return !isUrlDecoded ||
    // Request path must be absolute and not contain "..".
    requestPath.empty() || requestPath[0] != '/' || requestPath.find("..") != std::string::npos;
}

}// namespace leaf::server
