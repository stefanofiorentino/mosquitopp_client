#include <chrono>
#include <thread>
#include <functional>
#include "../../lib/include/mqtt.h"

#define CLIENT_ID "Client_ID"
#define BROKER_ADDRESS "localhost"
#define MQTT_PORT 1883;

int main(int argc, char *argv[])
{
    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();

    if (argc > 1)
    {
        strcpy(host, argv[1]);
    }

    bool finished = false;
    int numOfSentMessage = 0;
    mqtt_client iot_client(client_id, host, port, nullptr);

    std::string message("REQUEST");
    iot_client.publishAndWaitForResponseWithTimeout(message, []()
    {
#if DEBUG
    std::cout << "onReply" << std::endl;
#endif
    }, []()
    {
#if DEBUG
        std::cout << "onTimeout" << std::endl;
#endif
    });

    mosqpp::lib_cleanup();

    return 0;
}

