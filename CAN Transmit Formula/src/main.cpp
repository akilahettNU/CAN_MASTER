#include <Arduino.h>
#include <virtualTimer.h>
#include <CAN.h>

CAN g_can{};
VirtualTimerGroup g_canTimerGroup;

MakeSignedCANSignal(float, 0, 16, 0.01, 0.0) E_TestSignal;

CANTXMessage<1> g_TestMessage(
    g_can,           // CAN bus to use
    0x123,           // Message ID
    sizeof(float),   // Length of the message (bytes)
    100,             // Period in ms
    g_canTimerGroup, // Timer group to use
    E_TestSignal);

void sendfloatMessage()
{
  E_TestSignal = (float)3,1415;
  digitalWrite(2,1);
  delay(1);
  digitalWrite(2, 0);
  delay(1);
}
void tickCan()
{
  g_can.Tick();
}
void setup()
{
  g_can.Initialize(ICAN::BaudRate::kBaud1M);
  g_canTimerGroup.AddTimer(50,tickCan);
  g_canTimerGroup.AddTimer(100, sendfloatMessage);
  pinMode(2, OUTPUT);
}

void loop()
{
  g_canTimerGroup.Tick(millis());
}