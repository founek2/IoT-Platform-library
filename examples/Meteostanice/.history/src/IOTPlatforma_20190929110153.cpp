#include <PubSubClient.h>
#include <WiFiClientSecure.h>

const char fingerprint[] = "7C 77 E9 A0 BB 42 C5 1D 09 1B E4 BF 7F 9E 32 A7 54 AD 4C 19";
const char *mqtt_server = "192.168.10.202";
// const char *mqtt_server = "test.iotplatforma.cloud";

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

class IOTPlatforma
{
    char *API_KEY;

public:
    IOTPlatforma(char *apiKey) : API_KEY(apiKey)
    {
        randomSeed(micros());
        wifiClient.setFingerprint(fingerprint);
        client.setServer(mqtt_server, 8883);
    }
    boolean connect()
    {
        int counter = 0;
        while (!client.connected() && counter < 5)
        {
            Serial.print("Attempting MQTT connection...");
            // Create a random client ID
            String clientId = "ESP8266Client-";
            clientId += String(random(0xffff), HEX);
            ++counter;
            if (client.connect(clientId.c_str(), API_KEY, "kekel"))
            {
                Serial.println("connected");
                return true;
                // Once connected, publish an announcement...
                // client.publish("/kekel/outTopic", "hello world");
                // ... and resubscribe
                // client.subscribe("/kekel/inTopic");
            }
            else
            {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                // Wait 5 seconds before retrying
                delay(5000);
            }
        }
        return false;
    }
};