//Display

#ifndef __DISPLAY__
#define __DISPLAY__

#include <inttypes.h>

#define SEG_A   0b00000001
#define SEG_B   0b00000010
#define SEG_C   0b00000100
#define SEG_D   0b00001000
#define SEG_E   0b00010000
#define SEG_F   0b00100000
#define SEG_G   0b01000000
#define SEG_DP  0b10000000

#define DEFAULT_BIT_DELAY  100

class Display {

public:
  //! Inicializace displeje a nastavení PINů
  //!
  //! @param pinClk - Číslo digitálního PINu zapojeného do pinClk
  //! @param pinDIO - Číslo digitálního PINu zapojeného do pinDIO
  Display(uint8_t pinClk, uint8_t pinDIO, unsigned int bitDelay = DEFAULT_BIT_DELAY);

  //! Nastavení jasu displeje
  //!
  //! Spustí se pouze u změny dat zobrazených na displeji.
  //!
  //! @param od 0 (nejtmavší) do 7 (nejsvětlejší)
  void setBrightness(uint8_t brightness, bool on = true);

  void setSegments(const uint8_t segments[], uint8_t length = 4, uint8_t pos = 0);

  //! Vymaže data na displeji
  void clear();

  //! Zobrazí celé číslo.
  //!
  //!
  //! @param num Číslo, které se má vykreslit.
  //! @param leading_zero Pokud je nastaveno na true, zobrazí před čísly nuly. Neplatí u záporných čísel.
  //! @param length Počet číslic zobrazovaného čísla.
  //! @param pos Pozice čísla. (0 - nejvíce vlevo, 3 - nejvíce vpravo)
  void showNumberDec(int num, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);

  //! Tečky na displeji.
  //!
  //! @param num Číslo, které se má vykreslit.
  //! @param dots Zapíná tečky a dvojtečky.
  //! @param leading_zero Pokud je nastaveno na true, zobrazí před čísly nuly. Neplatí u záporných čísel.
  //! @param length Počet číslic zobrazovaného čísla.
  //! @param pos Pozice čísla. (0 - nejvíce vlevo, 3 - nejvíce vpravo)
  void showNumberDecEx(int num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);

  //! Přeloží číslo na segmentový kód.
  //!
  //! Funkce přijme číslo od 0-15 a přeloží ji do segmentového kódu.
  //! Čísla mezi 10-15 jsou přeloženy do Hex kódu. (A-F)
  //!
  //! @param digit Číslo mezi 0-15.
  //! @return A code representing the 7 segment image of the digit (LSB - segment A;
  //!         bit 6 - segment G; bit 7 - always zero)
  uint8_t encodeDigit(uint8_t digit);

protected:
   void bitDelay();

   void start();

   void stop();

   bool writeByte(uint8_t b);

   void showDots(uint8_t dots, uint8_t* digits);
   
   void showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots = 0, bool leading_zero = false, uint8_t length = 4, uint8_t pos = 0);


private:
	uint8_t m_pinClk;
	uint8_t m_pinDIO;
	uint8_t m_brightness;
	unsigned int m_bitDelay;
};

#endif