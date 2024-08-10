//
// Created by kok on 06.08.24.
//

#include "../include/authentication-app/Request.h"
#include "../include/authentication-app/RequestException.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

Request::Request(const string& url, roptions_t *options) {
    if (url.empty()) throw std::invalid_argument("Invalid request url!");
    this->url = url;
    req_handle.setOpt(cURLpp::Options::Url(url));

    std::list<std::string> standard_headers = {"Content-Type: application/json"};
    req_handle.setOpt(cURLpp::Options::HttpHeader(standard_headers));

    if (options != nullptr) {
        if (!options->headers.empty()) add_headers(options->headers);
        if (!options->queries.empty()) build_query_url(options->queries);
    }
}

void Request::build_query_url(vector<rquery_t>& queries) {
    int i = 0;
    for (rquery_t& query: queries) {
        query.key = cURLpp::escape(query.key);
        query.value = cURLpp::escape(query.value);
        string start_symbol = i == 0 ? "?" : "&";
        this->url += start_symbol + query.key + '=' + query.value;
        i++;
    }
}

void Request::add_headers(vector<rheader_t>& headers) {
    std::list<string> headers_list;
    for (const rheader_t& header: headers) {
        headers_list.push_back(header.key + ": " + header.value);
    }
    req_handle.setOpt(cURLpp::Options::HttpHeader(headers_list));
}

void Request::check_response_code(const string& raw_response) const {
    const unsigned int http_code = cURLpp::infos::ResponseCode::get(req_handle);
    if (http_code < 200 || http_code > 299) throw RequestException("Request failed! Raw response: " + raw_response);
}
