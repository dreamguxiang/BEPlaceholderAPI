#pragma once

struct Config {
    int  version                    = 1;
    std::string LangCode = "en_US";
    bool Chat = true;
    bool Sign = true;
};

namespace{
Config config;
}