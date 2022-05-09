//
// Created by LoicL on 24/12/2020.
//

#ifndef LEAF_STOCK_REPLIES_HPP
#define LEAF_STOCK_REPLIES_HPP

namespace leaf::http::response::stock_replies
{
constexpr char ok[] = "";
constexpr char created[] =
  "<html>"
  "<head><title>Created</title></head>"
  "<body><h1>201 Created</h1></body>"
  "</html>";
constexpr char accepted[] =
  "<html>"
  "<head><title>Accepted</title></head>"
  "<body><h1>202 Accepted</h1></body>"
  "</html>";
constexpr char no_content[] =
  "<html>"
  "<head><title>No Content</title></head>"
  "<body><h1>204 Content</h1></body>"
  "</html>";
constexpr char multiple_choices[] =
  "<html>"
  "<head><title>Multiple Choices</title></head>"
  "<body><h1>300 Multiple Choices</h1></body>"
  "</html>";
constexpr char moved_permanently[] =
  "<html>"
  "<head><title>Moved Permanently</title></head>"
  "<body><h1>301 Moved Permanently</h1></body>"
  "</html>";
constexpr char moved_temporarily[] =
  "<html>"
  "<head><title>Moved Temporarily</title></head>"
  "<body><h1>302 Moved Temporarily</h1></body>"
  "</html>";
constexpr char not_modified[] =
  "<html>"
  "<head><title>Not Modified</title></head>"
  "<body><h1>304 Not Modified</h1></body>"
  "</html>";
constexpr char bad_request[] =
  "<html>"
  "<head><title>Bad Request</title></head>"
  "<body><h1>400 Bad Request</h1></body>"
  "</html>";
constexpr char unauthorized[] =
  "<html>"
  "<head><title>Unauthorized</title></head>"
  "<body><h1>401 Unauthorized</h1></body>"
  "</html>";
constexpr char forbidden[] =
  "<html>"
  "<head><title>Forbidden</title></head>"
  "<body><h1>403 Forbidden</h1></body>"
  "</html>";
constexpr char not_found[] =
  "<html>"
  "<head><title>Not Found</title></head>"
  "<body><h1>404 Not Found</h1></body>"
  "</html>";
constexpr char internal_server_error[] =
  "<html>"
  "<head><title>Internal Server Error</title></head>"
  "<body><h1>500 Internal Server Error</h1></body>"
  "</html>";
constexpr char not_implemented[] =
  "<html>"
  "<head><title>Not Implemented</title></head>"
  "<body><h1>501 Not Implemented</h1></body>"
  "</html>";
constexpr char bad_gateway[] =
  "<html>"
  "<head><title>Bad Gateway</title></head>"
  "<body><h1>502 Bad Gateway</h1></body>"
  "</html>";
constexpr char service_unavailable[] =
  "<html>"
  "<head><title>Service Unavailable</title></head>"
  "<body><h1>503 Service Unavailable</h1></body>"
  "</html>";

std::string StatusToString(HttpResponse::Status status)
{
  switch (status)
  {
    case HttpResponse::Status::ok: return ok;
    case HttpResponse::Status::created: return created;
    case HttpResponse::Status::accepted: return accepted;
    case HttpResponse::Status::no_content: return no_content;
    case HttpResponse::Status::multiple_choices: return multiple_choices;
    case HttpResponse::Status::moved_permanently: return moved_permanently;
    case HttpResponse::Status::moved_temporarily: return moved_temporarily;
    case HttpResponse::Status::not_modified: return not_modified;
    case HttpResponse::Status::bad_request: return bad_request;
    case HttpResponse::Status::unauthorized: return unauthorized;
    case HttpResponse::Status::forbidden: return forbidden;
    case HttpResponse::Status::not_found: return not_found;
    case HttpResponse::Status::internal_server_error: return internal_server_error;
    case HttpResponse::Status::not_implemented: return not_implemented;
    case HttpResponse::Status::bad_gateway: return bad_gateway;
    case HttpResponse::Status::service_unavailable: return service_unavailable;
    default: return internal_server_error;
  }
}

}// namespace leaf::http::response::stock_replies

#endif// LEAF_STOCK_REPLIES_HPP
