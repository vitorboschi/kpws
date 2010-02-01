#include "webserver.h"

//microhttpd includes
//#include <platform.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

/*
void WebServer::incomingConnection(int socketDescriptor) {
	QTcpSocket *s;

	qDebug("Criando socket");
	s = new QTcpSocket(this);
	qDebug("Conectando socket");
	if (s->setSocketDescriptor(socketDescriptor)) {
		qDebug("Criando thread");
		WorkerThread* w = new WorkerThread(s, getContent() , this);
		qDebug("Iniciando thread");
		w->start();
	}
	else {
		qDebug("Erro conectando o socket");
		qDebug() << s->errorString();
	}
}
*/

void WebServer::setRootContent(WebContent* root) {
	rootContent = root;
}


WebContent* WebServer::getContent() {
	return rootContent;
}



//Callback functions

//Read at most max bytes from the source and put them in *buf. The actual number of bytes read must be returned
int contentReaderCallback (void *cls, uint64_t pos, char *buf, int max) {
  WebContent* wc = (WebContent*)cls;
  int ret;
  
  ret = wc->getChunk("",buf,(quint64) pos,max);
  return ret;
  
}

int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url,
const char *method, const char *version, const char *upload_data,
size_t *upload_data_size, void **con_cls)
{
  struct MHD_Response *response;
  int ret;
  WebContent* wc = (WebContent*)cls;
  qDebug("Respondendo requisicao. URL:");
  qDebug(url);
  
  if (wc->validUrl(url)) {
    //TODO: create a callback response
    response = MHD_create_response_from_callback(wc->getSize(url), 4096,
    &contentReaderCallback, wc, NULL);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    return ret;
  }
  else {
    //TODO: Get the error page from a template
    const char *page = "<html><body>Invalid address.</body></html>";
    
    response = MHD_create_response_from_data (strlen (page),
    (void*) page, MHD_NO, MHD_NO);
    
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);
    return ret;
  }
}


WebServer::WebServer() {
  daemon = NULL;
}

bool WebServer::startServer() {
  //TODO: Make Port number user configurable
  //TODO: Allow the user to select which ip address the server will use
  daemon = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION, 8080, NULL, NULL,
&answer_to_connection, rootContent, MHD_OPTION_END);
if (NULL != daemon) {
  return true;
}
else {
  return false;
}
}

void WebServer::stopServer() {
  if (NULL != daemon) {
    MHD_stop_daemon(daemon);
  }
  else {
    
  }
}