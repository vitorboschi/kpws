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
