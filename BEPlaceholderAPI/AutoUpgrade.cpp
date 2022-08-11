#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <LLAPI.h>
#include <Nlohmann/json.hpp>
#include <ServerAPI.h>
#include <SimpleIni/SimpleIni.h>
#include <Utils/CryptHelper.h>
#include <Utils/FileHelper.h>
#include <Utils/NetworkHelper.h>
#include <Utils/StringHelper.h>
#include <chrono>
#include <filesystem>
#include <httplib/httplib.h>
#include <process.h>
#include <seh_exception/seh_exception.hpp>
#include <string>
#include <thread>
#include "Global.h"

using json = nlohmann::json;
using namespace std;

void checkUpdate() {
    std::thread t([] {
        try {
            string infoUrl = "https://api.minebbs.com/api/openapi/v1/resources/4181/updates?page=1";
            string info;
            int status = -1;
            if (!HttpGetSync(infoUrl, &status, &info, 60) || status != 200) {
               // logger.info("Unable to check for updates. Download failed! Error Code: {}", status);
                return;
            }
            nlohmann::json data1 = nlohmann::json::parse(info, nullptr, true, true);
            if (data1.find("data") != data1.end()) {
                nlohmann::json data2 = data1["data"];
                LL::Version verRemote = LL::Version::parse(data2[0]["title"].get<string>());
                LL::Version verLocal = VERSION;
                if (verRemote > verLocal) {
                    logger.info("New version available: {}\n-->https://www.minebbs.com/resources/4181/\n-->https://github.com/LiteLDev/BEPlaceholderAPI/releases", verRemote.toString());
                }
                else {
                    logger.info("No new version available.");
                }
            }
        }
        catch (nlohmann::json::exception& e) {
            logger.info("An error occurred while parsing the update configuration, {}", e.what());

        }
        catch (const seh_exception& e) {
            logger.info("SEH Uncaught Exception Detected!\n{}", e.what());
            logger.info("In Auto Update system");

        }
        catch (...) {
            logger.info("An error was caught during the update process.");

        }
        });
    t.detach();
}