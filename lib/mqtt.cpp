#include "include/mqtt.h"

mqtt_client::mqtt_client(std::string const &id, std::string const &host, int port,
                         std::function<void(std::string const &)> const &onMessage) :
        mosquittopp(id.c_str()), onMessage(onMessage), rc(0) {
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host.c_str(), port, keepalive);
}

void mqtt_client::on_connect(int rc) {
    if (!rc) {
#ifdef DEBUG
        std::cout << "Connected - code " << rc << std::endl;
#endif
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos) {
#ifdef DEBUG
    std::cout << "Subscription succeeded." << std::endl;
#endif
}

void mqtt_client::on_message(const struct mosquitto_message *message) {
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

    memset(buf, 0, payload_size * sizeof *buf);

    /* Copy N-1 bytes to ensure always 0 terminated. */
    memcpy(buf, message->payload, MAX_PAYLOAD * sizeof(char));

    // call the callback
    if (onMessage) {
        onMessage(std::string(buf));
    }
}


void mqtt_client::loop_forever() {
    ::mosqpp::mosquittopp::loop_forever();
}
