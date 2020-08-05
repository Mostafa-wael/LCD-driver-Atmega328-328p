#ifndef LCD_commands
#define LCD_commands

#define lcdClear 0x01 // replace all chars by ASCII 'space'
#define lcdHome 0x02 // return cursor to first position first line

#define cursorToLeft 0x04 // shift cursor from right to left for Arabic
#define cursorToRight 0x06  // shift cursor from left to right for English
#define displayToRight 0x05
#define displayToLeft 0x07

#define dispayOff_cursorOff 0x08
#define dispayOff_cursorOn 0x0A
#define dispayOn_cursorOff 0x0C
#define dispayOn_cursorBlinking 0x0E
#define dispayOff_cursorBlinking 0x0F

#define cursorToBegining1stLine 0x80
#define cursorToBegining2ndLine 0xC0

#define lcdSet_8bits 0x38
#define lcdSet_4bits 0x28

#endif

