#include <Arduino.h>
#include <virtualTimer.h>
#include <CAN.h>


CAN g_can{};
VirtualTimerGroup g_canTimerGroup;

MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) float_rx_signal;

// CANTXMessage<1> g_TestMessage(
//     g_can,           // CAN bus to use
//     0x123,           // Message ID
//     sizeof(float),   // Length of the message (bytes)
//     100,             // Period in ms
//     g_canTimerGroup, // Timer group to use
//     E_TestSignal);
CANRXMessage<1> rx_message(
    g_can,
    0x123,
    []()
    { //Serial.println(rx_message.GetLastReceiveTime()); 
      digitalWrite(2,1);
      delay(1);
      digitalWrite(2,0);
      delay(1);
      Serial.println(float_rx_signal);
    },
    float_rx_signal
);

void tickCan()
{
  g_can.Tick();
}
void setup()
{
  g_can.Initialize(ICAN::BaudRate::kBaud1M);
  g_canTimerGroup.AddTimer(50, tickCan);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  g_canTimerGroup.Tick(millis());
}