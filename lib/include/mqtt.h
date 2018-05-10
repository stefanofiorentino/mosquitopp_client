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

#define REQUEST_TOPIC "REQUEST"
#define RESPONSE_TOPIC "RESPONSE"
#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
    int rc;
    std::function<void(std::string const &)> onMessage;

public:
    mqtt_client(const char *id, const char *host, int port, std::function<void(std::string const &)> const &onMessage);

    void on_connect(int rc) override;

    void on_subscribe(int mid, int qos_count, const int *granted_qos) override;

    void on_message(const struct mosquitto_message *message) override;

    void publishAndWaitForResponseWithTimeout(std::string const &message, std::function<void()> const &onReply, std::function<void()> const &onTimeout);
    void start_loop();

};

#endif //SIMPLECLIENT_MQTT_H
