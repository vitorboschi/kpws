/*
KDE Personal Web Server - Allow you to easily share files over http
Copyright (C) 2010 by Vitor Boschi da Silva (vitorboschi@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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
