//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_REQUEST_HANDLER_HPP
#define LEAF_REQUEST_HANDLER_HPP

#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "mime_type/mime_types.hpp"

namespace leaf::server
{
class RequestHandler
{
  public:
    RequestHandler(const RequestHandler &) = delete;

    RequestHandler &operator=(const RequestHandler &) = delete;

    /// Construct with a directory containing files to be served.
    explicit RequestHandler(std::string doc_root, mime_type::MimeTypes mimeTypes);

    /// Handle a request and produce a reply.
    void handleRequest(const http::request::HttpRequest &httpRequest, http::response::HttpResponse &httpResponse);

  private:
    /// The directory containing the files to be served.
    std::string _documentRoot;

    mime_type::MimeTypes _mimeTypes;

    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    static bool UrlDecode(const std::string &in, std::string &out);
};
}// namespace leaf::server

#endif// LEAF_REQUEST_HANDLER_HPP
