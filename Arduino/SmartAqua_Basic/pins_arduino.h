 /******************************************************************************************
  * FileName     : pins_arduino.h
  * Description  : to support arduino uno with ET-Upboard
  * Author       : SCS
  * CopyRight    : (주)한국공학기술연구원(www.ketri.re.kr)
  * Warning      : 
  * Created Date : 2022.10.03 : SCS : support arduino uno with ET-Upboard
  * Modified     : 
 ******************************************************************************************/
 
#if defined(ARDUINO_AVR_UNO)   

//static const uint8_t LED_BUILTIN = 5;
//#define BUILTIN_LED  LED_BUILTIN // backward compatibility
//#define LED_BUILTIN LED_BUILTIN

static const uint8_t D2 =  2;   // BUILTIN_LED_Red
static const uint8_t D3 =  3;   // BUILTIN_LED_Blue
static const uint8_t D4 =  4;   // BUILTIN_LED_Green
static const uint8_t D5 =  5;   // BUILTIN_LED_Yellow
static const uint8_t D6 =  6;   // BUILTIN_BUTTON_Red
static const uint8_t D7 =  7;   // BUILTIN_BUTTON_Blue
static const uint8_t D8 =  8;   // BUILTIN_BUTTON_Green
static const uint8_t D9 =  9;    // BUILTIN_BUTTON_Yellow

#endif /* Pins_Arduino_h */
