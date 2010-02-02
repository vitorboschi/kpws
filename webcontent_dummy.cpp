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

#include "webcontent_dummy.h"

#include <QTextStream>

WebContent_Dummy::WebContent_Dummy(QString identifier) : WebContent(identifier) {
	//init the buffer
	QTextStream stream(&content, QIODevice::WriteOnly);
	stream << "<html>\n<head>\n<title>Hello World</title>\n</head>\n";
	stream << "<body>Hello World from " << identifier << "</body>\n</html>";
	stream.flush();

}

int WebContent_Dummy::getChunk(QString url, QByteArray* buffer, qint64 start, int len)
{
	if (url == "") {
		buffer->clear();
		if (start <= content.length()) {
			buffer->append(content.mid(start, len));
			return content.mid(start, len).size(); //OK
		}
		else {
			return -1; //invalid parameters
		}
	}
	else {
		return -1; //Not found
	}
}

QString WebContent_Dummy::getMime(QString url) {
	if (url == "") {
		return "text/html";
	}
	else {
		return "";
	}
}

qint64 WebContent_Dummy::getSize(QString url) {
	if (url == "") {
		return content.length();
	}
	return 0;
}

bool WebContent_Dummy::validUrl(QString url) {
	return (url == "");
}


