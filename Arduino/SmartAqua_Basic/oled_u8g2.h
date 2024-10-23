/********************************************************************************** 
 * Author       : SCS
 * Date         : 2018.09.30  
 * Modified     : 2022.10.03 : SCS : support arduino uno with ET-Upboard
 * Modified     : 2023.10.11 : SCS : decrease memory for arduino
 * Modified     : 2024.07.11 : SCS : add 5 line, 8 line
 * Modified     : 2024.07.19 : SCS : add setLine(int line, String buffer)
 * Modified     : 2024.07.21 : SCS : add two setLine()
**********************************************************************************/

#ifndef OLED_U8G2_H
#define OLED_U8G2_H

#include <Arduino.h>

class OLED_U8G2{

private:  
  static const int MAX_LINES = 8;
  char* lineString[MAX_LINES];

public:
  OLED_U8G2();
  void setup(void);
  void clearDisplay(void);
  void setLine(int line, const char* buffer);
  void setLine(int line, String buffer);
  void setLine(int line, int buffer); 
  void setLine(int line, float buffer, int decimal_point);
  void display(int display_line = 3); 
};

#endif

//=================================================================================
// End of Line
//=================================================================================
