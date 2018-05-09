#include <chrono>
#include <thread>
#include <functional>
#include "include/mqtt.h"

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
    mqtt_client iot_client(client_id, host, port,
                           [&iot_client, &finished, &numOfSentMessage](std::string const &message)
                           {
                               // Examples of messages for M2M communications...
                               // mosquitto_pub -t EXAMPLE_TOPIC -m "STATUS"
                               if (!strcmp(message.c_str(), "STATUS"))
                               {
                                   if (numOfSentMessage < 1)
                                   {
                                       iot_client.publish(NULL, PUBLISH_TOPIC, strlen(message.c_str()),
                                                          message.c_str());
                                       numOfSentMessage++;
                                       std::cout << "Status request re-sent: " << message << std::endl;
                                       return;
                                   }
                                   #ifdef DEBUG
                                       std::cout << "Status request received: " << message << std::endl;
                                   #endif
                               }
                           });

    iot_client.start_loop();

    while (!finished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    mosqpp::lib_cleanup();

    return 0;
}

