//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_STATUS_STRINGS_HPP
#define LEAF_STATUS_STRINGS_HPP

#include <string>

namespace Leaf::Http::StatusStrings {
    const std::string ok =
            "HTTP/1.0 200 OK\r\n";
    const std::string created =
            "HTTP/1.0 201 Created\r\n";
    const std::string accepted =
            "HTTP/1.0 202 Accepted\r\n";
    const std::string no_content =
            "HTTP/1.0 204 No Content\r\n";
    const std::string multiple_choices =
            "HTTP/1.0 300 Multiple Choices\r\n";
    const std::string moved_permanently =
            "HTTP/1.0 301 Moved Permanently\r\n";
    const std::string moved_temporarily =
            "HTTP/1.0 302 Moved Temporarily\r\n";
    const std::string not_modified =
            "HTTP/1.0 304 Not Modified\r\n";
    const std::string bad_request =
            "HTTP/1.0 400 Bad Request\r\n";
    const std::string unauthorized =
            "HTTP/1.0 401 Unauthorized\r\n";
    const std::string forbidden =
            "HTTP/1.0 403 Forbidden\r\n";
    const std::string not_found =
            "HTTP/1.0 404 Not Found\r\n";
    const std::string internal_server_error =
            "HTTP/1.0 500 Internal Server Error\r\n";
    const std::string not_implemented =
            "HTTP/1.0 501 Not Implemented\r\n";
    const std::string bad_gateway =
            "HTTP/1.0 502 Bad Gateway\r\n";
    const std::string service_unavailable =
            "HTTP/1.0 503 Service Unavailable\r\n";

    boost::asio::const_buffer ToBuffer(Models::Http::HttpResponse::Status status) {
        switch (status) {
            case Models::Http::HttpResponse::Status::ok:
                return boost::asio::buffer(ok);
            case Models::Http::HttpResponse::Status::created:
                return boost::asio::buffer(created);
            case Models::Http::HttpResponse::Status::accepted:
                return boost::asio::buffer(accepted);
            case Models::Http::HttpResponse::Status::no_content:
                return boost::asio::buffer(no_content);
            case Models::Http::HttpResponse::Status::multiple_choices:
                return boost::asio::buffer(multiple_choices);
            case Models::Http::HttpResponse::Status::moved_permanently:
                return boost::asio::buffer(moved_permanently);
            case Models::Http::HttpResponse::Status::moved_temporarily:
                return boost::asio::buffer(moved_temporarily);
            case Models::Http::HttpResponse::Status::not_modified:
                return boost::asio::buffer(not_modified);
            case Models::Http::HttpResponse::Status::bad_request:
                return boost::asio::buffer(bad_request);
            case Models::Http::HttpResponse::Status::unauthorized:
                return boost::asio::buffer(unauthorized);
            case Models::Http::HttpResponse::Status::forbidden:
                return boost::asio::buffer(forbidden);
            case Models::Http::HttpResponse::Status::not_found:
                return boost::asio::buffer(not_found);
            case Models::Http::HttpResponse::Status::internal_server_error:
                return boost::asio::buffer(internal_server_error);
            case Models::Http::HttpResponse::Status::not_implemented:
                return boost::asio::buffer(not_implemented);
            case Models::Http::HttpResponse::Status::bad_gateway:
                return boost::asio::buffer(bad_gateway);
            case Models::Http::HttpResponse::Status::service_unavailable:
                return boost::asio::buffer(service_unavailable);
            default:
                return boost::asio::buffer(internal_server_error);
        }
    }
}

#endif //LEAF_STATUS_STRINGS_HPP
