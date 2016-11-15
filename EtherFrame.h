#ifndef ETHERFRAME_H
#define ETHERFRAME_H
#include "MacAddress.h"
#include "Arduino.h"
#include "stdlib.h"
#include "string.h"
#include "Utils.h"

enum EtherTypes : unsigned short { 
                  ETH_IPv4        = 0x0800,
                  ETH_ARP         = 0x0806,
                  ETH_WOL         = 0x0842,
                  ETH_IETF_TRILL  = 0x22F3,
                  ETH_DEC         = 0x6003,
                  ETH_RARP        = 0x8035,
                  ETH_APT_ET      = 0x809B,
                  ETH_IPv6        = 0x86DD,
                  ETH_MPLS        = 0x8848,
                  ETH_LLDP        = 0x88CC
};
                  

class EtherFrame{
public:
  EtherFrame(char *data, int length){
    mDstMac = MacAddress(data);
    mSrcMac = MacAddress(data+6);
    mEthertype = ushortFromBytes(data, 12);
    //mPayload = (char*)malloc(length-18);
    mPayloadLen = length-18;
    mPayload = data+14;
    //memcpy(mPayload, data+14, length-18);
    mCRC = *(data+length-4);
  }

  ~EtherFrame(){
    if(mPayload){
      //free(mPayload);
    }
  }

  MacAddress mDstMac;
  MacAddress mSrcMac;
  char *mPayload;
  int mPayloadLen;
  unsigned short mEthertype;
  unsigned int mCRC;

};
#endif
