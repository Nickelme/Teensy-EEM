#include "IP.h"
#include "Utils.h"

void IPHandler::HandleProtocol(EtherFrame ethFrm){
  
  if(ethFrm.mEthertype == EtherTypes::ETH_IPv4){
    if((ethFrm.mPayload[0] >> 4) == 4){
      Serial.print("\tIPv4: ");
      IPv4Packet packet(ethFrm);
      Serial.print(packet.mSrcAddr.asString());
      Serial.print(" to ");
      Serial.println(packet.mDstAddr.asString());
    }else{
      Serial.println("\tEthernet Frame says Ipv4 but version isn't 4");
    }
  }else if(ethFrm.mEthertype == EtherTypes::ETH_IPv6){
    if((ethFrm.mPayload[0] >> 4) == 6){
      Serial.println("\tIs Ipv6");
    }else{
      Serial.println("\tEthernet Frame says Ipv6 but version isn't 6");
    }
  }
}

IPv4Packet::IPv4Packet(EtherFrame ethFrm){
  mVerIHL = ethFrm.mPayload[0];
  mDSCP_ECN = ethFrm.mPayload[1];
  mTotalLength = ushortFromBytes(ethFrm.mPayload, 2);
  mIdentification = ushortFromBytes(ethFrm.mPayload, 4);
  mFlagsFragmentOffset = ushortFromBytes(ethFrm.mPayload,6);
  mTTL = ethFrm.mPayload[8];
  mProtocol = ethFrm.mPayload[9];
  mHeaderCheckSum = ushortFromBytes(ethFrm.mPayload, 10);
  mSrcAddr = IPv4Address(uintFromBytes(ethFrm.mPayload, 12)); 
  mDstAddr = IPv4Address(uintFromBytes(ethFrm.mPayload, 16));
  int iphl = getIPHeaderSize();
  if(iphl > 20){
    mOptions = ethFrm.mPayload+20;
  }
  mPayloadLen = ethFrm.mPayloadLen-iphl;
  mPayload = ethFrm.mPayload+iphl;
}

