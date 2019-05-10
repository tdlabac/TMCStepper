#if defined(ARDUINO_ARCH_AVR)
  #define getPort(P) digitalPinToPort(P)
  #define writeMOSI_H *mosi_register |= mosi_bm
  #define writeMOSI_L *mosi_register &= ~mosi_bm
  #define writeSCK_H *sck_register |= sck_bm
  #define writeSCK_L *sck_register &= ~sck_bm
  #define readMISO *miso_register & miso_bm
#elif defined(ARDUINO_ARCH_SAM) // DUE:1.2MHz
  // by stimmer https://forum.arduino.cc/index.php?topic=129868.msg980466#msg980466
  #define writeMOSI_H g_APinDescription[mosi_pin].pPort -> PIO_SODR = g_APinDescription[mosi_pin].ulPin
  #define writeMOSI_L g_APinDescription[mosi_pin].pPort -> PIO_CODR = g_APinDescription[mosi_pin].ulPin
  #define writeSCK_H g_APinDescription[sck_pin].pPort -> PIO_SODR = g_APinDescription[sck_pin].ulPin
  #define writeSCK_L g_APinDescription[sck_pin].pPort -> PIO_CODR = g_APinDescription[sck_pin].ulPin
  #define readMISO !!(g_APinDescription[miso_pin].pPort -> PIO_PDSR & g_APinDescription[miso_pin].ulPin)
#elif defined(TARGET_LPC1768)
  #define writeMOSI_H gpio_set(mosi_pin)
  #define writeMOSI_L gpio_clear(mosi_pin)
  #define writeSCK_H gpio_set(sck_pin)
  #define writeSCK_L gpio_clear(sck_pin)
  #define readMISO gpio_get(miso_pin)
#else // DUE:116kHz
  #define writeMOSI_H digitalWrite(mosi_pin, HIGH)
  #define writeMOSI_L digitalWrite(mosi_pin, LOW)
  #define writeSCK_H digitalWrite(sck_pin, HIGH)
  #define writeSCK_L digitalWrite(sck_pin, LOW)
  #define readMISO digitalRead(miso_pin)
#endif