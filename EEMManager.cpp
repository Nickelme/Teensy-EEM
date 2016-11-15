#include "EEMManager.h"
#include "Utils.h"
#include "IP.h"

EEMManager::EEMManager(MacAddress CurrentAddress){
  mCurrentAddress = CurrentAddress;
  EEM.begin();
  EEM.setTimeout(100000);
  IPHandler *ipHand = new IPHandler();
  setProtocolHandler(EtherTypes::ETH_IPv4, ipHand);
  setProtocolHandler(EtherTypes::ETH_IPv6, ipHand);
}

void EEMManager::Loop(){
  int bytesReady = EEM.available();
  if(bytesReady < 2){
    return;
  }
  unsigned short eemHdr;
  int amtRead = EEM.readBytes((char*)&eemHdr, 2);
  if(bitRead(eemHdr, 15)){
    //TODO: Handle Command Packets
  }else{
    HandleEEMData(eemHdr);
  }
  
}

void EEMManager::HandleEEMData(unsigned short eemHdr){
  int EtherFrmSize = eemHdr & 0x3FFF;
  char EtherFrmData[EtherFrmSize];
  int amtRead = EEM.readBytes(EtherFrmData, EtherFrmSize);
  if(amtRead != EtherFrmSize){
    Serial.println("Error Etherframe didnt equal Supposed Size");
    return;
  }
  EtherFrame EtherFrm(EtherFrmData, EtherFrmSize);
  Serial.print("New EthernetFrame from: ");
  Serial.print(EtherFrm.mSrcMac.asString());
  Serial.print(" to ");
  Serial.print(EtherFrm.mDstMac.asString());
  Serial.print(" EtherType ");
  Serial.println(padHexShort(EtherFrm.mEthertype));
  std::map<EtherTypes, ProtocolHandler*>::iterator it = mProtocolHandlers.find(EtherTypes(EtherFrm.mEthertype));
  if(it != mProtocolHandlers.end()){
    it->second->HandleProtocol(EtherFrm);
  }
  
}

