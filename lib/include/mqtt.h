#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H

#include <mosquittopp.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <functional>
#include <thread>

#ifdef DEBUG
#include <iostream>
#endif

#define PUBLISH_TOPIC "EXAMPLE_TOPIC"
#define MQTT_TOPIC "EXAMPLE_TOPIC"
#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
    int rc;
    std::function<void(std::string const &)> onMessage;

public:
    mqtt_client(std::string const &, std::string const &, int port, std::function<void(std::string const &)> const &onMessage);

    void on_connect(int rc) final;

    void on_subscribe(int mid, int qos_count, const int *granted_qos) final;

    void on_message(const struct mosquitto_message *message) final;

    void loop_forever();
};

#endif //SIMPLECLIENT_MQTT_H
