#include <Arduino.h>
#include <MCP2515.h>
#include <SPI.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

const int pinLed = 3;

void setup() {
    pinMode(pinLed, OUTPUT);
    SPI.begin();
    Serial.begin(115200);
    mcp2515.reset();
    mcp2515.setBitrate(CAN_50KBPS, MCP_16MHZ);
    mcp2515.setNormalMode();

    Serial.println("receiver started");

     digitalWrite(pinLed, HIGH);
     delay(500);
     digitalWrite(pinLed, LOW);
}

void loop() {
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
        Serial.println("received");
        Serial.println(canMsg.can_id);
        Serial.print(0x036);
        if (canMsg.can_id == 0x036) {
            int x = canMsg.data[0];
            Serial.print("buttonValue: ");
            Serial.println(x);
            digitalWrite(pinLed, x);
        }
    }
}
