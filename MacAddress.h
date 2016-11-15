#ifndef MACADDRESS_H
#define MACADDRESS_H
#include "Arduino.h"
class MacAddress {
public:
  MacAddress(char *addr){
    mAddr[0] = addr[0];
    mAddr[1] = addr[1];
    mAddr[2] = addr[2];
    mAddr[3] = addr[3];
    mAddr[4] = addr[4];
    mAddr[5] = addr[5];
  }

  MacAddress(String addr){
    mAddr[0] = strtol(addr.substring(0,2).c_str(), NULL, 16);
    mAddr[1] = strtol(addr.substring(3,5).c_str(), NULL, 16);
    mAddr[2] = strtol(addr.substring(6,8).c_str(), NULL, 16);
    mAddr[3] = strtol(addr.substring(9,11).c_str(), NULL, 16);
    mAddr[4] = strtol(addr.substring(12,14).c_str(), NULL, 16);
    mAddr[5] = strtol(addr.substring(15,17).c_str(), NULL, 16);
  }

  MacAddress(){
    mAddr[0] = 0;
    mAddr[1] = 0;
    mAddr[2] = 0;
    mAddr[3] = 0;
    mAddr[4] = 0;
    mAddr[5] = 0;
  }

  char *getAddress(){
    return mAddr;
  }

  String asString(){
    return String(toHex(mAddr[0]) + ":" + toHex(mAddr[1]) + ":" + toHex(mAddr[2]) + ":" + toHex(mAddr[3]) + ":" + toHex(mAddr[3]) + ":" + toHex(mAddr[5]));
  }

private:
  char mAddr[6];

  String toHex(char b){
    String hex(b, HEX);
    if(hex.length() == 1){
      hex = String("0") + hex;
    }
    return hex;
  }
};
#endif

