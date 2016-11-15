#ifndef IP_H
#define IP_H
#include "EEMManager.h"
#include "Arduino.h"

class IPHandler : public ProtocolHandler {
public:
  IPHandler() {}
  virtual void HandleProtocol(EtherFrame ethFrm);
};

class IPv4Address {
public:
  IPv4Address(String addr){
    int index = addr.indexOf('.');
    mAddress += ((unsigned int)strtol(addr.substring(0,index).c_str(), NULL, 10)) << 24;
    int lastIndex = index+1;
    index = addr.indexOf('.', lastIndex);
    mAddress += ((unsigned int)strtol(addr.substring(lastIndex,index).c_str(), NULL, 10)) << 16;
    lastIndex = index+1;
    index = addr.indexOf('.', lastIndex);
    mAddress += ((unsigned int)strtol(addr.substring(lastIndex,index).c_str(), NULL, 10)) << 8;
    mAddress += ((unsigned int)strtol(addr.substring(index+1,addr.length()).c_str(), NULL, 10));
  }

  IPv4Address(unsigned int addr){
    mAddress = addr;
  }

  IPv4Address(){
    mAddress = 0;
  }

  unsigned int getUnsignedInt(){
    return mAddress;
  }

  String asString(){
    String sAddr = "";
    sAddr += String((mAddress>>24&0xFF)) + ".";
    sAddr += String((mAddress>>16&0xFF)) + ".";
    sAddr += String((mAddress>>8&0xFF)) + ".";
    sAddr += String((mAddress>>0&0xFF));
    return sAddr;
  }

private: 
  unsigned int mAddress;
};

class IPv4Packet {
public:

  IPv4Packet(EtherFrame ethFrm);
  IPv4Packet(){};

  int getIPHeaderSize() { return (mVerIHL&15)*4; }

  char mVerIHL;
  char mDSCP_ECN;
  unsigned short mTotalLength;
  unsigned short mIdentification;
  unsigned short mFlagsFragmentOffset;
  char mTTL;
  char mProtocol;
  unsigned short mHeaderCheckSum;
  IPv4Address mSrcAddr;
  IPv4Address mDstAddr;
  char *mOptions;
  char *mPayload;
  int mPayloadLen;
};


#endif
