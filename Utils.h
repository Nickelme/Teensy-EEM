#ifndef TEENSY_EEM_UTILS_H
#define TEENSY_EEM_UTILS_H
#include "Arduino.h"

inline String padHex(char b){
  String hex(b, HEX);
  if(hex.length() == 1){
    hex = String("0") + hex;
  }
  return hex;
}

inline String padHexShort(short s){
  char f = s >> 8;
  char b = s;
  String fp = padHex(f);
  String bp = padHex(b);
  return String(fp+bp);
  
}

inline unsigned short ushortFromBytes(char *data, int index){
  return (((unsigned short)data[index]) << 8) + ((unsigned short)(data[index+1]));
}

inline unsigned int uintFromBytes(char *data, int index){
  return (((unsigned int)data[index]) << 24) + (((unsigned int)data[index+1]) << 16) + (((unsigned int)data[index+2]) << 8) + (((unsigned int)data[index+3]));
}


#endif
