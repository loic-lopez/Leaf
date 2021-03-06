//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_REQUEST_HANDLER_HPP
#define LEAF_REQUEST_HANDLER_HPP

#include "models/http/http_request.hpp"
#include "models/http/http_response.hpp"
#include "models/mime_types.hpp"

namespace Leaf::LeafServer::Http {
    class RequestHandler {
    public:
        RequestHandler(const RequestHandler &) = delete;

        RequestHandler &operator=(const RequestHandler &) = delete;

        /// Construct with a directory containing files to be served.
        explicit RequestHandler(std::string doc_root, Models::MimeTypes mimeTypes);

        /// Handle a request and produce a reply.
        void handleRequest(const Models::Http::HttpRequest &httpRequest, Models::Http::HttpResponse &httpResponse);

    private:
        /// The directory containing the files to be served.
        std::string _documentRoot;

        Models::MimeTypes _mimeTypes;

        /// Perform URL-decoding on a string. Returns false if the encoding was
        /// invalid.
        static bool UrlDecode(const std::string &in, std::string &out);
    };
}

#endif //LEAF_REQUEST_HANDLER_HPP
