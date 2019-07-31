#ifndef ESP8266_WEB_FASTLED_MUSIC_WEBSERVER_H
#define ESP8266_WEB_FASTLED_MUSIC_WEBSERVER_H


#include <ESPAsyncWebServer.h>
#include <config/config.h>

class WebServer {
public:
    explicit WebServer();

    ~WebServer();

    void listen();

private:
    AsyncWebServer server = AsyncWebServer(WEB_SERVER_PORT);

    void configure();

    static void notFound(AsyncWebServerRequest *request);
};


#endif //ESP8266_WEB_FASTLED_MUSIC_WEBSERVER_H
