#ifndef EEMMANAGER_H
#define EEMMANAGER_H
#include "MacAddress.h"
#include "EtherFrame.h"
#include "Arduino.h"
#include <map>

class ProtocolHandler {
	public:
		virtual void HandleProtocol(EtherFrame) = 0;
};

class EEMManager {
public:
	EEMManager(MacAddress CurrentAddress);
	void Loop();

	void setProtocolHandler(EtherTypes type, ProtocolHandler* handler){
		mProtocolHandlers[type] = handler;
	}

	void sendData(char *data, unsigned int len);
	

private:
	MacAddress mCurrentAddress; 

	void HandleEEMData(unsigned short eemHdr);
	void HandleEEMControl(unsigned short eemHdr);

	std::map<EtherTypes, ProtocolHandler*> mProtocolHandlers;
};
#endif
