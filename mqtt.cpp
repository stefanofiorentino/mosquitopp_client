#include "include/mqtt.h"

mqtt_client::mqtt_client(const char *id, const char *host, int port, std::function<void(std::string const &)> const &func) :
        mosquittopp(id)
{
    int keepalive = DEFAULT_KEEP_ALIVE;
    mqtt_client::func = func;
    connect(host, port, keepalive);
}

void mqtt_client::on_connect(int rc)
{
    if (!rc)
    {
        #ifdef DEBUG
            std::cout << "Connected - code " << rc << std::endl;
        #endif
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
    #ifdef DEBUG
        std::cout << "Subscription succeeded." << std::endl;
    #endif
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

    if(!strcmp(message->topic, PUBLISH_TOPIC))
    {
        memset(buf, 0, payload_size * sizeof(char));

        /* Copy N-1 bytes to ensure always 0 terminated. */
        memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));

        // call the callback
        func(std::string(buf));
    }
}

void mqtt_client::start_loop()
{
    std::thread mosquittopp_thread([this]()
                                   {
                                       subscribe(NULL, MQTT_TOPIC);
                                       rc = loop();
                                       while (1)
                                       {
                                           rc = loop();
                                           if (rc)
                                           {
                                               reconnect();
                                               subscribe(NULL, MQTT_TOPIC);
                                           }
                                           std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                       }

                                   });
    mosquittopp_thread.detach();
}