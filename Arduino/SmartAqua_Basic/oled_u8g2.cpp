/********************************************************************************** 
 * Author : SCS
 * Date : 2018.09.30  
 * Description : SSD1306 OLED Display  
 * Reference: FontUsage.ino in u8g2 examples 
 * Modified     : 2022.10.03 : SCS : support arduino uno with ET-Upboard
 * Modified     : 2023.10.11 : SCS : decrease memory for arduino
 * Modified     : 2024.07.11 : SCS : add 5 line, 8 line
 * Modified     : 2024.07.19 : SCS : add setLine(int line, String buffer)
 * Modified     : 2024.07.21 : SCS : add two setLine()
 **********************************************************************************/

#include "oled_u8g2.h"

#include <Arduino.h>

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// 2018.09.05 : SCS
// U8g2 Contructor (Frame Buffer)
#if defined(ARDUINO_AVR_UNO)    
  // Slow  
  U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ A0, /* data=*/ A1, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
  // Fast & No Flickering
  //U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);         
#elif defined(ESP32)   
  // Fast
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#else
  #error "Unknown board"
#endif
// End of constructor

//=================================================================================
OLED_U8G2::OLED_U8G2() 
//=================================================================================  
{
  lineString[0] = (char*) "";
  lineString[1] = (char*) "";
  lineString[2] = (char*) "";
  lineString[3] = (char*) "";
  lineString[4] = (char*) "";
  lineString[5] = (char*) "";
  lineString[6] = (char*) "";   
}

#if defined(ARDUINO_AVR_UNO)    
//=================================================================================
void OLED_U8G2::setup(void) 
//=================================================================================
{
  u8x8.begin();  
  u8x8.setFont(u8x8_font_8x13B_1x2_r);
  //u8x8.setBusClock(4000000);
}

//=================================================================================
void OLED_U8G2::clearDisplay() 
//=================================================================================
{ 
  // Clear 
  u8x8.clearDisplay();   
}  
  
//=================================================================================
void OLED_U8G2::display() 
//=================================================================================
{ 
  // First line  
  u8x8.drawString(0, 0, lineString[0]);

  //Second line
  u8x8.drawString(0, 2, lineString[1]);

  // Third line
  u8x8.drawString(0, 4, lineString[2]);
  
  // Display
  u8x8.refreshDisplay(); 
}

#elif defined(ESP32)   
//=================================================================================
void OLED_U8G2::setup(void) 
//=================================================================================
{
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
}
//=================================================================================
void OLED_U8G2::display(int display_line) 
//=================================================================================
{ 
  // Clear 
  u8g2.clearBuffer();          // clear the internal memory

  if (display_line <= 3) {
    // First line
    u8g2.setFont(u8g2_font_9x15B_tf); 
    
    u8g2.setCursor(0,10);
    u8g2.print(lineString[0]);

    // Second line
    u8g2.setFont(u8g2_font_logisoso18_tf ); 
    u8g2.setCursor(0,35);
    u8g2.print(lineString[1]);  

    // Third line
    u8g2.setCursor(0,60);
    u8g2.print(lineString[2]);
  }
  
  else if (display_line <= 5) {
    // First line
    u8g2.setFont(u8g2_font_9x15B_tf);     
    u8g2.setCursor(0,10);
    u8g2.print(lineString[0]);
    
    u8g2.setFont( u8g2_font_crox1cb_mr );
    for(int r=1; r<display_line; r++) {
      u8g2.setCursor(0, r*12+13);
      u8g2.print(lineString[r]);
    } 
  }    
 
  else if (display_line <= 8) {
    u8g2.setFont( u8g2_font_pcsenior_8r );   // 글자가 작아서 넓은 간격으로해야 가독성
    for(int r=0; r<display_line; r++) {
      u8g2.setCursor(0, r*8+6);
      u8g2.print(lineString[r]);
    } 
  }  
  
  // Display
  u8g2.sendBuffer();          // transfer internal memory to the display
}
#else
  #error "Unknown board"
#endif

//=================================================================================
void OLED_U8G2::setLine(int line, const char* buffer)    // 문자 배열
//=================================================================================
{  
  if (line < 1 || line > MAX_LINES) return;
  lineString[line - 1] = (char *)buffer;  
}

//=================================================================================
void OLED_U8G2::setLine(int line, String buffer)  // 문자열
//=================================================================================
{   
  if (line < 1 || line > MAX_LINES) return;  
  
  // lineString[line - 1]이 nullptr이 아니고, 동적으로 할당된 메모리를 가리키고 있는지 확인
  if (lineString[line - 1] != nullptr && lineString[line - 1] != "") {
    free(lineString[line - 1]);
    lineString[line - 1] = nullptr;  // 해제 후 nullptr로 설정
  }  
  
  // 새로운 문자열을 위한 메모리를 할당합니다
  size_t len = buffer.length() + 1;
  lineString[line - 1] = (char*)malloc(len);
  
  // 메모리 할당이 성공했는지 확인합니다
  if (lineString[line - 1] != nullptr) {
    // String의 내용을 새로 할당된 메모리에 복사합니다
    strncpy(lineString[line - 1], buffer.c_str(), len);
    lineString[line - 1][len - 1] = '\0';  // null 종료 문자 확실히 추가
  }  
}

//=================================================================================
void OLED_U8G2::setLine(int line, int buffer)  // 정수
//=================================================================================
{
  if (line < 1 || line > MAX_LINES) return;

  // 정수를 문자열로 변환
  String intString = String(buffer);

  // String 버전의 setLine 함수 호출
  setLine(line, intString);
}

//=================================================================================
void OLED_U8G2::setLine(int line, float buffer, int decimal_point)  // 실수
//=================================================================================
{
  if (line < 1 || line > MAX_LINES) return;

  // 실수를 문자열로 변환
  String floatString = String(buffer, decimal_point);

  // String 버전의 setLine 함수 호출
  setLine(line, floatString);
}
 
//=================================================================================
// End of Line
//=================================================================================
