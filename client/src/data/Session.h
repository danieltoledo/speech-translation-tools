#pragma once

#include "User.h"
#include "Config.h"

#include "../data/message.h"

#include <list>
#include <cstring>
#include <stdio.h>
#include <cstdlib> 
#include "../lib/eventtype.h"
#include "../lib/Subject.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#endif
#include <wx/richtext/richtextctrl.h>
#include <wx/grid.h> 


#include "../GlobalVariables.h"


typedef std::list<UserPTR> UserList;
typedef std::shared_ptr<UserList> UserListPTR;

/* 
 * Set and get functions
 */

class Session{
public:
	static Session* Instance();
	bool sound_flag;			//Flag to start/stop 
	bool tts_flag;				//Flag to start/stop TextToSpeech 		
	bool write_flag;			//Flag to recognize Typing
	bool tasto_stt_flag;		//Flag to activate Automatic SpeechToText
	bool finish_ctrl_flag;		//Flag to recognize CTRL press button
	bool automatic_stt_flag;
	uint64 scHandlerID;
	private:
	Session();  // Private so that it can  not be called
	Session(Session const&){};             // copy constructor is private
	Session& operator=(Session const&){};  // assignment operator is private
	static Session* m_pInstance;
 
public:
	/*static Session* Instance();*/

	char* Session::getGoogleURLTranslation();

	bool getsound_flag(){ return sound_flag; }
	void setsound_flag(bool conf){ this->sound_flag = conf; }
	
	bool gettts_flag(){ return tts_flag; }
	void settts_flag(bool conf){ this->tts_flag = conf; }

	bool getwrite_flag(){ return write_flag; }
	void setwrite_flag(bool conf){ this->write_flag = conf; }

	bool gettasto_stt_flag(){ return tasto_stt_flag; }
	void settasto_stt_flag(bool conf){ this->tasto_stt_flag = conf; }

	bool getfinish_ctrl_flag(){ return finish_ctrl_flag; }
	void setfinish_ctrl_flag(bool conf){ this->finish_ctrl_flag = conf; }

	bool getautomatic_stt_flag(){ return automatic_stt_flag; }
	void setautomatic_stt_flag(bool conf){ this->automatic_stt_flag = conf; }

	ConfigPTR getConfig(){ return m_config; }
	void setConfig(ConfigPTR conf){ this->m_config = conf; }

	UserListPTR getListUser(){ return m_luser; }
	void setListUser(UserListPTR luser){ this->m_luser = luser; }



	MessageQueuePTR getMessageQueue(){ return m_queue; }

	char* Session::getApiGoogle();

	UserPTR getUser(const char* name);
	void addNewUser(UserPTR u);
	void deleteUser(UserPTR u);
	bool checkUser(UserPTR u);	
	bool checkUser(const char* u);

	void addMsgToLog(MessagePTR msg);


/*	static wxRichTextCtrl *chatptr;				//Pointer to edit the chatptr
	static unsigned int curRow;			//Initialize Row index
	static unsigned int curCol;			//Initialize Column index
	static wxGrid *gridptr;					//Pointer to edit the chatptr grid*/

private:
	Session* m_instance;
	ConfigPTR m_config;
	UserListPTR m_luser;
	char* m_translationEngine;
	MessageQueuePTR m_queue;
};


