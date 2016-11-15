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
		HandleEEMControl(eemHdr);
	}else{
		HandleEEMData(eemHdr);
	}
	
}

void EEMManager::HandleEEMControl(unsigned short eemHdr){
	switch(eemHdr >> 2 & 7){
		case 0:
			Serial.println("\tEcho Request");
			break;

		case 1:
			Serial.println("\tEcho Response");
			break;
				
		case 2:
			Serial.println("\tSuspendHint");
			break;
				
		case 3:
			Serial.println("\tResponseHint");
			break;

		case 4:
			Serial.println("\tResponseCompleteHint");
			break;

		case 5:
			Serial.println("\tTickle");
			break;

		case 6:
			Serial.println("\tReserved 6");
			break;

		case 7:
			Serial.println("\tReserved 7");
			break;
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

