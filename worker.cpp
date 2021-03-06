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

#include "worker.h"

Worker::Worker ( int socketDescriptor, WebContent* content, QObject* parent ) : QObject (parent)
{
  m_state = KPWS_STATE_IDLE;
  m_handled = false;
  m_position = 0;
  m_rootContent = content;
  m_buffer = new QByteArray(1024 * 1024, '\0'); //TODO: make the array size configurable
  
  m_socket = new QTcpSocket(this);
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(slotReadReady()));
  //connect(m_socket, SIGNAL(delayedCloseFinished()), this, SLOT(discardClient()));
  connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(slotBytesWritten(qint64)));
  m_socket->setSocketDescriptor(socketDescriptor);
}


Worker::~Worker()
{
  delete(m_buffer);
}

void Worker::slotBytesWritten ( qint64 bytes )
{
  //qDebug() << "Bytes Written: " << bytes << ". Current position: " << m_position;
  qint64 bytesRead;
  
  if (m_state == KPWS_STATE_ERROR) { //we got an invalid request
    m_socket->close();
    //emit error signal;
    return;
  }
  
  bytesRead = m_rootContent->getChunk(m_url, m_buffer, m_position, m_buffer->size());
  
  if (bytesRead == 0) {
    //end of data
    qDebug() << "End of data";
    m_socket->close();
    emit finished();
    return;
  }
  
  if (bytesRead < 0) {
    qDebug() << "Something bad happened";
    m_socket->close();
    //TODO: Emit error signal
    return;
  }
  
  m_socket->write(*m_buffer);
  m_position += bytesRead;
}

void Worker::slotReadReady() {
  if (!m_socket->canReadLine()) { //wait for more data before attempting to answer the request
    return;
  }
  
  if (m_handled) { //this request was already handled
    return;
  }
  
  m_handled = true;
  QString httpRequest(m_socket->readLine());
  if (httpRequest.section(" ", 0,0) != "GET") {
    //TODO: Send error response
    replyError(400, "Error");
    qDebug() << "Invalid request";
    return;
  }
  
  QString mime;
    
  //<TODO>must also handle absolute url (i.e. http://something...)
  m_url = httpRequest.section(" ", 1, 1).section("/", 1); //strip the first slash
  qDebug() << "Stripped url is: " << m_url;
  
  //check if the resource really exist in this server
  if (!m_rootContent->validUrl(m_url)) {
    //TODO: send error 404: Not Found
    replyError(404, "Not Found");
    qDebug() << "Invalid URL";
    return;
  }

  //Create the response header
  QByteArray headerBlock;
  QTextStream header(&headerBlock, QIODevice::WriteOnly);
  
  header << "HTTP/1.1 200 OK\r\n";
  mime = m_rootContent->getMime(m_url);
  
  if (!mime.isEmpty()) {
    header << "Content-Type: " << mime << "\r\n";
  }
  //TODO: If the size is known, send it in the header
  
  header << "Connection: close\r\n";
  header << "\r\n";
  header.flush();
  
  //Send it
  m_state = KPWS_STATE_REPLYING;
  m_socket->write(headerBlock);
  
  //the response body will be written by slotBytesWritten
}

void Worker::replyError(int code, QString description)
{
  m_state = KPWS_STATE_ERROR;
  QByteArray headerBlock;
  QTextStream header(&headerBlock, QIODevice::WriteOnly);
  header << "HTTP/1.1 " << code << " " << description << "\r\n";
  header << "Connection: close\r\n";
  header.flush();
  m_socket->write(headerBlock);
}

void Worker::slotError(QTcpSocket::SocketError socketError) {
  
}

