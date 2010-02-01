#include "webcontent_dummy.h"

#include <QTextStream>

WebContent_Dummy::WebContent_Dummy(QString identifier) : WebContent(identifier) {
	//init the buffer
	QTextStream stream(&content, QIODevice::WriteOnly);
	stream << "<html>\n<head>\n<title>Hello World</title>\n</head>\n";
	stream << "<body>Hello World from " << identifier << "</body>\n</html>";
	stream.flush();

}

int WebContent_Dummy::getChunk(QString url, char* buffer, quint64 start, int len)
{
	
	if (url == "") {
		if (start <= content.length()) {
			size_t real_len = content.size() - start; //remaining bytes
			if (len < real_len) {
			  real_len = len; //copy only the amount requested
			}
			  
			memcpy(buffer,content.mid(start, len).constData(),real_len);
			return real_len; //O
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


