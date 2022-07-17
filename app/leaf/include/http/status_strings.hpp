//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_STATUS_STRINGS_HPP
#define LEAF_STATUS_STRINGS_HPP

#include "library/constexpr_map.hpp"

#include <boost/asio/buffer.hpp>

#include <string>

namespace leaf::http::response::status_strings
{

using namespace std::string_view_literals;// NOSONAR

static constexpr library::ConstexprMap<HttpResponse::Status, std::string_view, 16> MappedStatus {
  {HttpResponse::Status::ok, "HTTP/1.0 200 OK\r\n"sv},
  {HttpResponse::Status::created, "HTTP/1.0 201 Created\r\n"sv},
  {HttpResponse::Status::accepted, "HTTP/1.0 202 Accepted\r\n"sv},
  {HttpResponse::Status::no_content, "HTTP/1.0 204 No Content\r\n"sv},
  {HttpResponse::Status::multiple_choices, "HTTP/1.0 300 Multiple Choices\r\n"sv},
  {HttpResponse::Status::moved_permanently, "HTTP/1.0 301 Moved Permanently\r\n"sv},
  {HttpResponse::Status::moved_temporarily, "HTTP/1.0 302 Moved Temporarily\r\n"sv},
  {HttpResponse::Status::not_modified, "HTTP/1.0 304 Not Modified\r\n"sv},
  {HttpResponse::Status::bad_request, "HTTP/1.0 400 Bad Request\r\n"sv},
  {HttpResponse::Status::unauthorized, "HTTP/1.0 401 Unauthorized\r\n"sv},
  {HttpResponse::Status::forbidden, "HTTP/1.0 403 Forbidden\r\n"sv},
  {HttpResponse::Status::not_found, "HTTP/1.0 404 Not Found\r\n"sv},
  {HttpResponse::Status::internal_server_error, "HTTP/1.0 500 Internal Server Error\r\n"sv},
  {HttpResponse::Status::not_implemented, "HTTP/1.0 501 Not Implemented\r\n"sv},
  {HttpResponse::Status::bad_gateway, "HTTP/1.0 502 Bad Gateway\r\n"sv},
  {HttpResponse::Status::service_unavailable, "HTTP/1.0 503 Service Unavailable\r\n"sv},
};

static inline boost::asio::const_buffer ToAsioBuffer(const HttpResponse::Status status)
{
  constexpr auto mappedStatusEnd     = status_strings::MappedStatus.end();
  constexpr auto internalServerError = status_strings::MappedStatus.at(HttpResponse::Status::internal_server_error);
  auto value                         = status_strings::MappedStatus.at(status);

  if (value == mappedStatusEnd) value = internalServerError;

  return boost::asio::buffer(value->second);
}

}// namespace leaf::http::response::status_strings

#endif// LEAF_STATUS_STRINGS_HPP
