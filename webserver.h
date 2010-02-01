#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "webcontent.h"

class WebServer
{
	public:
		WebServer();
		void stopServer();
		bool startServer();
		void setRootContent(WebContent* root);
		WebContent* getContent();
	protected:
		//void incomingConnection(int socketDescriptor);
		WebContent* rootContent;
		struct MHD_Daemon *daemon;

};

#endif
