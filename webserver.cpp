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

#include "webserver.h"
#include "worker.h"

void WebServer::incomingConnection(int socketDescriptor) {
  qDebug("Spawning Worker...");
  Worker* w = new Worker(socketDescriptor, getContent(), this);
  //TODO: Connect signals/slots from worker
}

void WebServer::setRootContent(WebContent* root) {
	rootContent = root;
}

WebContent* WebServer::getContent() {
	return rootContent;
}

bool WebServer::startServer() {
  //TODO: Make Port number user configurable
  //TODO: Allow the user to select which ip address the server will use
}

void WebServer::stopServer() {

}
