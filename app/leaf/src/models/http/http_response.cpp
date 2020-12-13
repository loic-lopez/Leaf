//
// Created by LoicL on 24/12/2020.
//

#include "models/http/http_response.hpp"

namespace MiscStrings {

    const char name_value_separator[] = {':', ' '};
    const char crlf[] = {'\r', '\n'};

}

std::vector<boost::asio::const_buffer> Leaf::Models::Http::HttpResponse::toBuffers() {
    std::vector<boost::asio::const_buffer> buffers;

    buffers.push_back(Leaf::Http::StatusStrings::ToBuffer(status));
    for (auto &header : headers) {
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

Leaf::Models::Http::HttpResponse
Leaf::Models::Http::HttpResponse::StockReply(Leaf::Models::Http::HttpResponse::Status status) {
    HttpResponse httpResponse;
    httpResponse.status = status;
    httpResponse.content = Leaf::Http::StockReplies::ToString(status);
    httpResponse.headers.resize(2);
    httpResponse.headers[0].name = "Content-Length";
    httpResponse.headers[0].value = std::to_string(httpResponse.content.size());
    httpResponse.headers[1].name = "Content-Type";
    httpResponse.headers[1].value = "text/html";
    return httpResponse;
}