#pragma once

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif

#include "../gui/ClientTsFrm.h"
#include "../data/Session.h"
#include "../data/Message.h"
#include "../data/Config.h" 

#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/stattext.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/grid.h>
#include "../gui\NationList.h"
#include "../gui\NationInfo.h"
//#include "..\gui\LoginWarnings.h"
#include "../ArchiveLog.h"

#include "../GlobalVariables.h"
#include "../translateController/translateController.h"
#include "../translateController/translateVariable.h"
/*#include "../gui/FrmMailSending.h"
#include "../gui/FrmSettingMail.h"
#include "../gui/AudioWizard.h"*/
#include <list>
#include <functional>
#include "../data/Subject.h"

#include "../data/Event.h"

//#include "../gui/FrmSaveChat.h"

#define MENU_ESCI 1800
#define MENU_OPZIONI 1801
#define MENU_SPEECH 1802

/*class ClientTsFrm; 

typedef std::function<void(const ClientTsFrm&)> cbClientTsFrm;*/



class ClientTS : public Subject{
	Session* session;
	ConfigPTR config;
	bool flagSave;
	char LANG_MSG_SRC[500];
	char MSG_SRC[500];

public:
	ClientTS(){
		session->Instance();
		config = session->getConfig();
	}
	~ClientTS(){}
	
	char* getLANG_MSG_SRC(){ return LANG_MSG_SRC;}

	char* getMSG_SRC(){ return MSG_SRC; }

	bool getFlagSave(){ return flagSave;}

	void setFlagSave(bool flg){ flagSave = flg;} 

	static void speak(char *LANG, char*MSG);
	static void Print(char*word);
	static size_t read_callback(static void *ptr, size_t size, size_t nmemb, static void *userp);
	static void writeWaveFile(const char* filename, SAudioStreamFormat format, static void* data);
	static void SetupColor();
	static void onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
	static void onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID);
	static void onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	static void onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier);
	static void onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
	static void onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility); 
	static void onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage);
	static void onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID);
	static void onIgnoredWhisperEvent(uint64 serverConnectionHandlerID, anyID clientID);
	static void onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
	static void onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString);
	static void onCustomPacketEncryptEvent(char** dataToSend, unsigned int* sizeOfData);
	static void onCustomPacketDecryptEvent(char** dataReceived, unsigned int* dataReceivedSize);
	static void onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask);
	static void showChannels(uint64 serverConnectionHandlerID);
	static void showChannelClients(uint64 serverConnectionHandlerID, uint64 channelID);
	static void onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message);
	static void showClients(uint64 serverConnectionHandlerID);
	static void createChannel(uint64 serverConnectionHandlerID, const char *name);
	static void deleteChannel(uint64 serverConnectionHandlerID);
	static void renameChannel(uint64 serverConnectionHandlerID);
	static void switchChannel(uint64 serverConnectionHandlerID);
	static void toggleVAD(uint64 serverConnectionHandlerID);
	static void setVadLevel(uint64 serverConnectionHandlerID);
	static void requestWhisperList(uint64 serverConnectionHandlerID);
	static void requestClearWhisperList(uint64 serverConnectionHandlerID);
	static void toggleRecordSound(uint64 serverConnectionHandlerID);
	static int readIdentity(char* identity);
	static int writeIdentity(const char* identity);
};

struct user* getPerson();
char* getLANG_MSG_SRC();
char* getMSG_SRC();
//void registercb(cbClientTsFrm fn);


DWORD WINAPI TTS_THREAD(LPVOID lpParameter);
DWORD WINAPI CTRL_STT(LPVOID lpParameter);
DWORD WINAPI ClientStart(LPVOID lpParameter);
DWORD WINAPI STT_THREAD(LPVOID lpParameter);
