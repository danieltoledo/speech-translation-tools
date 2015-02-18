#pragma once

#include "User.h"
#include "Config.h"

#include <list>
#include <cstring>
#include <stdio.h>
#include <cstdlib>

typedef std::list<UserPTR> UserList;
typedef std::shared_ptr<UserList> UserListPTR;

/* 
 * Set and get functions
 */
 
class Session{
public:
	static Session* Instance();
	private:
	Session();  // Private so that it can  not be called
	Session(Session const&){};             // copy constructor is private
	Session& operator=(Session const&){};  // assignment operator is private
	static Session* m_pInstance;
 
public:
	/*static Session* Instance();*/

	char* Session::getGoogleURLTranslation();

	ConfigPTR getConfig(){ return _config; }
	void setConfig(ConfigPTR conf){ this->_config = conf; }

	UserListPTR getListUser(){ return _luser; }
	void setListUser(UserListPTR luser){ this->_luser = luser; }

	char* Session::getApiGoogle();


	UserPTR getUser(const char* name);
	void addNewUser(UserPTR u);
	void deleteUser(UserPTR u);
	bool checkUser(UserPTR u);	
	bool checkUser(const char* u);


private:
	Session* _instance;
	ConfigPTR _config;
	UserListPTR _luser;
	char* _translationEngine;
};


