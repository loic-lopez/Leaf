//
// Created by LoicL on 24/12/2020.
//

#ifndef __LEAF_STOCK_REPLIES_HPP__
#define __LEAF_STOCK_REPLIES_HPP__

#include "library/constexpr_map.hpp"

#include <string_view>

namespace leaf::http::response::stock_replies
{

using std::string_view_literals::operator""sv;

static constexpr library::ConstexprMap<HttpResponse::Status, std::string_view, 16> MappedStatus {
  {HttpResponse::Status::ok, ""sv},
  {HttpResponse::Status::created,
   "<html>"
   "<head><title>Created</title></head>"
   "<body><h1>201 Created</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::accepted,
   "<html>"
   "<head><title>Accepted</title></head>"
   "<body><h1>202 Accepted</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::no_content,
   "<html>"
   "<head><title>No Content</title></head>"
   "<body><h1>204 Content</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::multiple_choices,
   "<html>"
   "<head><title>Multiple Choices</title></head>"
   "<body><h1>300 Multiple Choices</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::moved_permanently,
   "<html>"
   "<head><title>Moved Permanently</title></head>"
   "<body><h1>301 Moved Permanently</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::moved_temporarily,
   "<html>"
   "<head><title>Moved Temporarily</title></head>"
   "<body><h1>302 Moved Temporarily</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::not_modified,
   "<html>"
   "<head><title>Not Modified</title></head>"
   "<body><h1>304 Not Modified</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::bad_request,
   "<html>"
   "<head><title>Bad Request</title></head>"
   "<body><h1>400 Bad Request</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::unauthorized,
   "<html>"
   "<head><title>Unauthorized</title></head>"
   "<body><h1>401 Unauthorized</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::forbidden,
   "<html>"
   "<head><title>Forbidden</title></head>"
   "<body><h1>403 Forbidden</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::not_found,
   "<html>"
   "<head><title>Not Found</title></head>"
   "<body><h1>404 Not Found</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::internal_server_error,
   "<html>"
   "<head><title>Internal Server Error</title></head>"
   "<body><h1>500 Internal Server Error</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::not_implemented,
   "<html>"
   "<head><title>Not Implemented</title></head>"
   "<body><h1>501 Not Implemented</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::bad_gateway,
   "<html>"
   "<head><title>Bad Gateway</title></head>"
   "<body><h1>502 Bad Gateway</h1></body>"
   "</html>"sv},
  {HttpResponse::Status::service_unavailable,
   "<html>"
   "<head><title>Service Unavailable</title></head>"
   "<body><h1>503 Service Unavailable</h1></body>"
   "</html>"sv},
};

static inline std::string_view StatusToStockReply(const HttpResponse::Status status)
{
  constexpr auto mappedStatusEnd     = MappedStatus.end();
  constexpr auto internalServerError = MappedStatus.at(HttpResponse::Status::internal_server_error);
  auto value                         = status_strings::MappedStatus.at(status);

  if (value == mappedStatusEnd) value = internalServerError;

  return value->second;
}

}// namespace leaf::http::response::stock_replies

#endif// __LEAF_STOCK_REPLIES_HPP__
