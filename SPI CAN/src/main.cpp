// #include <SPI.h>
// #include <mcp2515.h>
// #include <arduino.h>

// struct can_frame canMsg;
// MCP2515 mcp2515(10);

// void setup()
// {
//   Serial.begin(115200);

//   mcp2515.reset();
//   mcp2515.setBitrate(CAN_1000KBPS);
//   mcp2515.setNormalMode();

//   Serial.println("------- CAN Read ----------");
//   Serial.println("ID  DLC   DATA");
// }

// void loop()
// {
//   if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
//   {
//     Serial.print(canMsg.can_id, HEX); // print ID
//     Serial.print(" ");
//     Serial.print(canMsg.can_dlc, HEX); // print DLC
//     Serial.print(" ");

//     for (int i = 0; i < canMsg.can_dlc; i++)
//     { // print the data
//       Serial.print(canMsg.data[i], HEX);
//       Serial.print(" ");
//     }

//     Serial.println();
//   }
// }
#include <arduino.h>
#include <SPI.h>
#include <mcp2515.h>



struct can_frame canMsg;
struct MCP2515 mcp2515(17); // CS pin is GPIO 5

#define CAN_ACK_ID 0x123 // CAN ID for acknowledgment

void setup()
{
  Serial.begin(115200);


  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.println("Board Started");
}

void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    // if (canMsg.can_id == CAN_ACK_ID) // Check if the message is from the sender
    // {
    //   // int tempInt = (canMsg.data[0] << 8) | canMsg.data[1]; // Combine MSB and LSB
    //   // float temperatureC = tempInt / 100.0;                 // Convert back to float

    //   Serial.print("Temperature received: ");
    //   Serial.print(canMsg.data[0]);
    //   Serial.print(" ");
    //   Serial.println(canMsg.data[1]);

    // }

    uint16_t raw_value = canMsg.data[1] << 8 | canMsg.data[0]; // Little-endian format

    // Apply the scaling factor to convert it back to the original float value
    float decoded_value = raw_value * 0.01;

    Serial.print("Data received: ");
    Serial.print(canMsg.can_id, HEX);
    Serial.print(" ");
    Serial.print(canMsg.can_dlc);
    Serial.print(" ");
    Serial.println(decoded_value);
    //   Serial.print(canMsg.data[0]);
    //   Serial.print(" ");
    //   Serial.print(canMsg.data[1]);
    //   Serial.print(" ");
    //   Serial.print(canMsg.data[2]);
    //   Serial.print(" ");
    //   Serial.println(canMsg.data[3]);
    // }
  }

}