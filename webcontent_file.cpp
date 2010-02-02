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

#include "webcontent_file.h"

#include <QTextStream>
#include <QDataStream>
#include <KIO/NetAccess>
#include <QFile>

#include <QtDebug>

WebContent_File::WebContent_File(QString identifier, QString file) : WebContent(identifier) {
	this->file = file;

	if( KIO::NetAccess::download(file, tmpFile, NULL)) {
		qDebug() << "File " << file << " opened succefully as " << tmpFile;
		initOk = true;
	} else {
		qDebug() << "Error opening file " << file << ": " << KIO::NetAccess::lastErrorString();

		//init buffer with the error message
		QTextStream stream(&content, QIODevice::WriteOnly);
		stream << "<html>\n<head>\n<title>Error</title>\n</head>\n";
		stream << "<body>The file " << file << " could not be opened</body>\n</html>";
		stream.flush();
		initOk = false;
	}
}

int WebContent_File::getChunk(QString url, QByteArray* buffer, qint64 start, int len)
{
  //FIXME: This is very very inefficient
	if (url == "") {
		buffer->clear();
		QFile f(this->tmpFile);
		f.open(QIODevice::ReadOnly);
		QByteArray tempBuffer;
		
		if (f.seek(start)) {
			if (len >= 0 && f.bytesAvailable() >= len) {
				tempBuffer = f.peek(len);
			}
			else {
				tempBuffer = f.peek(f.bytesAvailable());
			}

			f.close();
			buffer->append(tempBuffer);
			return tempBuffer.size();
		}
		else {
			qDebug() << "ERROR: Tried to read past the end of file";
			f.close();
			return -1;
		}
	}
	else {
		return -1; //Not found
	}
}

QString WebContent_File::getMime(QString url) {
	if (url == "" && initOk) {
		return KIO::NetAccess::mimetype(tmpFile, NULL);
	}
	else if (url == "" && !initOk) {
		return "text/html";
	}
	else {
		return "";
	}
}

qint64 WebContent_File::getSize(QString url) {
	//<TODO>

	/*
	if (url == "" && initOk) {
		return content.length();
	}
	*/
	return 0;
}

bool WebContent_File::validUrl(QString url) {
	return (url == "");
}

WebContent_File::~WebContent_File() {
	KIO::NetAccess::removeTempFile(tmpFile);
}

