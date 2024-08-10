//
// Created by kok on 06.08.24.
//

#ifndef JSONPARSEABLE_H
#define JSONPARSEABLE_H

#include <nlohmann/json.hpp>

using nlohmann::json;

class JSONParseable {
public:
    virtual ~JSONParseable() = default;
    void to_json(json& j, const JSONParseable& p);
    void from_json(const json& j, JSONParseable& p);
};

#endif //JSONPARSEABLE_H
