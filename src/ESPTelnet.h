/* ------------------------------------------------- */

// TODO: add timestamp
// TODO: add pipe operator >
// TODO: ip & mac addr. an die event handler übergeben

/* ------------------------------------------------- */
#pragma once

#ifndef ESPTelnet_h
#define ESPTelnet_h
/* ------------------------------------------------- */
#include "Arduino.h"
#include <ESP8266WiFi.h>          // https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
#include <ESP8266WebServer.h>     // https://www.arduino.cc/en/Tutorial/WiFiWebServer
/* ------------------------------------------------- */
class ESPTelnet {
  typedef void (*CallbackFunction) ();

  public:
    ESPTelnet()                                   { isConnected = false; }

    bool begin();
    void loop();
    void stop()                                   { server.stop(); }


    void print(String str);
    void println(String str)                      { client.print(str + "\n"); }
    void println()                                { client.print("\n"); }

    String getIP()                                { return ip; }
    String getLastAttemptIP()                     { return attemptIp; }
    
    void onConnect(CallbackFunction f)            { on_connect = f; }
    void onConnectionAttempt(CallbackFunction f)  { on_connection_attempt = f; }
    void onReconnect(CallbackFunction f)          { on_reconnect = f; }
    void onDisconnect(CallbackFunction f)         { on_disconnect = f; }
    
  protected:
    WiFiServer server = WiFiServer(23);
    WiFiClient client;
    String ip = "";
    String attemptIp = "";
    boolean isConnected = false;

    CallbackFunction on_connect;
    CallbackFunction on_reconnect;
    CallbackFunction on_disconnect;
    CallbackFunction on_connection_attempt;  
};
/* ------------------------------------------------- */
  // << operator
  template<class T> inline ESPTelnet &operator <<(ESPTelnet &obj, T arg) { obj.print(arg); return obj; } 
/* ------------------------------------------------- */
#endif
/* ------------------------------------------------- */
