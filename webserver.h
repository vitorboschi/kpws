#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "webcontent.h"
#include <QTcpServer>

class WebServer : public QTcpServer
{
	public:
		void stopServer();
		bool startServer();
		void setRootContent(WebContent* root);
		WebContent* getContent();
	protected:
		void incomingConnection(int socketDescriptor);
		WebContent* rootContent;

};

#endif
