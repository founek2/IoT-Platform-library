#include "IOTPlatforma.h"

const char *ssid = "Zahrada";
const char *password = "1414elektron151";

const char *API_KEY = "fabd3f35584f8e4818a48eb3375119bc"; //v2.iotplatforma.cloud

bool RELAY_STATE = false;
int REALY_PIN = 0;

void callbackSwitch(const JsonVariant &payload);
IOTPlatforma plat(API_KEY, IOTPlatforma::CONTROL_MODE);

const String keys[] = {"rgb"};
const String defaultData[] = {"{\"on\":1}"};

void setup() {
   pinMode(REALY_PIN, OUTPUT);
   digitalWrite(LOW, REALY_PIN);

   plat.wifi(ssid, password);
    plat.setCallback("switch", callbackSwitch);
    // plat.clearTopic();
    // plat.saveTopic("/5d5554843beb3f419f9e4a64/garden/garage/gate");
    plat.enableOTA("123456777");
    plat.init();
    // TODO načíst předchozí uloženou barvu v EEPROM - asi přidat funkcionalitu do knihovny na uložení custom atributů
    plat.sendInitControl(defaultData, keys, 1);
}

void loop() {
     plat.loop();
}

void callbackSwitch(JsonVariant &jsonObj) // 1/0 || { type: "linear", color: #4242, on: 1, bright: 0-100}
{
    if (!jsonObj["on"].isNull())
    {
        int enabled = jsonObj["on"];
        if (enabled)
          digitalWrite(LOW, REALY_PIN);
        else
          digitalWrite(HIGH, REALY_PIN);
    }
}