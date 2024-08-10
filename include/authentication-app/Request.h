//
// Created by kok on 06.08.24.
//

#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <sstream>
#include <vector>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>

#include "JSONParseable.h"
#include "Request.h"

using std::cout, std::endl, std::string, std::vector, std::ostringstream;
using nlohmann::json;

struct rquery_t {
    string key;
    string value;
};

struct rheader_t {
    string key;
    string value;
};

struct roptions_t {
    vector<rquery_t> queries = {};
    vector<rheader_t> headers = {};
};

class Request {
public:
    explicit Request(const string& url, roptions_t *options = nullptr);
    Request(const Request& src) = delete;
    template<typename R>
    R get();
    template<typename R, typename B>
    R post(const B& body);
    template<typename R, typename B>
    R put(const B& body);
private:
    cURLpp::Easy req_handle;
    string url;

    void build_query_url(vector<rquery_t>& queries);
    void add_headers(vector<rheader_t>& headers);
    void check_response_code(const string& raw_response) const;
};

template<typename R>
R Request::get() {
    static_assert(std::is_base_of<JSONParseable, R>::value, "Response must be derived from JSONParseable!");

    ostringstream stream;
    req_handle.setOpt(cURLpp::Options::WriteStream(&stream));
    req_handle.perform();
    check_response_code(stream.str());
    return json::parse(stream.str()).get<R>();
}

template<typename R, typename B>
R Request::post(const B& body) {
    static_assert(std::is_base_of<JSONParseable, R>::value, "Response must be derived from JSONParseable!");
    static_assert(std::is_base_of<JSONParseable, B>::value, "Body must be derived from JSONParseable!");

    json json_body = body;
    string body_str = json_body.dump(0);
    ostringstream stream;
    req_handle.setOpt(cURLpp::Options::WriteStream(&stream));
    req_handle.setOpt(cURLpp::Options::PostFields(body_str));
    req_handle.setOpt(cURLpp::Options::PostFieldSize((long)body_str.size()));
    req_handle.perform();
    check_response_code(stream.str());
    return json::parse(stream.str()).get<R>();
}

template<typename R, typename B>
R Request::put(const B &body) {
    static_assert(std::is_base_of<JSONParseable, R>::value, "Response must be derived from JSONParseable!");
    static_assert(std::is_base_of<JSONParseable, B>::value, "Body must be derived from JSONParseable!");
    json json_body = body;
    string body_str = json_body.dump(0);
    ostringstream stream;
    req_handle.setOpt(cURLpp::Options::WriteStream(&stream));
    req_handle.setOpt(cURLpp::Options::PostFields(body_str));
    req_handle.setOpt(cURLpp::Options::PostFieldSize((long)body_str.length()));
    req_handle.setOpt(cURLpp::Options::CustomRequest("PUT"));
    req_handle.perform();
    check_response_code(stream.str());
    return json::parse(stream.str()).get<R>();
}

#endif //REQUEST_H
