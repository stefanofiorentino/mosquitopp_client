#include <chrono>
#include <thread>
#include <functional>

#include "../../lib/include/mqtt.h"

namespace {
    const std::string CLIENT_ID{"Client_ID"};
    const std::string BROKER_ADDRESS{"localhost"};
    const int MQTT_PORT{60000};
    const std::string TOPIC{"topic"};
}

int main(int argc, char *argv[]) {

    mosqpp::lib_init();

    mqtt_client iot_client(CLIENT_ID, BROKER_ADDRESS, MQTT_PORT, [](std::string const &message) {
#ifdef DEBUG
        std::cout << "Status request received: " << message << std::endl;
#endif
    });

    iot_client.subscribe(nullptr, TOPIC.c_str());
    iot_client.loop_forever();
    mosqpp::lib_cleanup();
    return 0;
}
