/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTcpSocket>
#include "webcontent.h"

class Worker : public QObject
{
  Q_OBJECT
  public:
    Worker(int socketDescriptor, WebContent* content, QObject* parent);
    ~Worker();
    
  signals:
    void error(QTcpSocket::SocketError socketError);
    void finished();

  private:
    typedef enum {
      KPWS_STATE_IDLE,
      KPWS_STATE_REPLYING,
      KPWS_STATE_ERROR
    } KPWS_State;
    
    void replyError(int code, QString description);
    
    QTcpSocket* m_socket;
    WebContent* m_rootContent;
    quint64 m_position; //where the next block of data begins
    bool m_handled;
    QByteArray* m_buffer;
    QString m_url;
    KPWS_State m_state;
    
  private slots:
    void slotReadReady();
    void slotError(QTcpSocket::SocketError socketError);
    void slotBytesWritten(qint64 bytes);
};

#endif // WORKER_H
