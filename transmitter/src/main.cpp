#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

/*
MCP2515 Module  -> Arduino
VCC             -> +5V
GND             -> GND
CS              -> 10 (SPI_SS)
SO              -> 12 (SPI_MISO)
SI              -> 11 (SPI_MOSI)
SCK             -> 13 (SPI_SCK)
INT             -> 2
*/

struct can_frame canMsg;
MCP2515 mcp2515(10);

const int pinButton = 3;
bool buttonValue;

void setup() {
    pinMode(pinButton, INPUT_PULLUP);
    buttonValue = digitalRead(pinButton);

    SPI.begin();
    Serial.begin(115200);
    mcp2515.reset();
    mcp2515.setBitrate(CAN_50KBPS, MCP_16MHZ);
    mcp2515.setNormalMode();
}

void loop() {
    if (digitalRead(pinButton) != buttonValue) {
        Serial.print("button press: ");
        buttonValue = !buttonValue;
        Serial.println(buttonValue);

        canMsg.can_id = 0x036;  //CAN id as 0x036
        canMsg.can_dlc = 8;     //CAN data length as 8
        canMsg.data[0] = buttonValue;
        canMsg.data[1] = 0X00;
        canMsg.data[2] = 0x00;
        canMsg.data[3] = 0x00;
        canMsg.data[4] = 0x00;
        canMsg.data[5] = 0x00;
        canMsg.data[6] = 0x00;
        canMsg.data[7] = 0x00;
        mcp2515.sendMessage(&canMsg);  //Sends the CAN message

        delay(100);
    }
}
