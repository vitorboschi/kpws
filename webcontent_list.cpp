#include <QTextStream>
#include <QtDebug>
#include "webcontent_list.h"

WebContent_List::WebContent_List(QString identifier) : WebContent(identifier) {
}

bool WebContent_List::addContent(WebContent* content) {
	resources[content->getIdentifier()] = content;
	content->setParent(this);

	//<TODO> should I add some kind of checking here?
	return true;
}

WebContent* WebContent_List::getContent(QString identifier) {
	if (resources.contains(identifier)) {
		return resources[identifier];
	}
	else {
		return NULL;
	}
}

WebContent* WebContent_List::removeContent(QString identifier) {
	if (resources.contains(identifier)) {
		WebContent* buffer = resources[identifier];
		resources.remove(identifier);
		return buffer;
	}
	else {
		return NULL;
	}
}

QString WebContent_List::getMime(QString url) {
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);

	if (url == "") { //the resource is this list itself
		return "text/html";
	}
	else if (resources.contains(id)) {
		return (resources[id]->getMime(address));
	}
	else { //not found
		return "";
	}
}

qint64 WebContent_List::getSize(QString url) {
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);

	if (url == "") { //the resource is this list itself
		return 0;
	}
	else if (resources.contains(id)) {
		return (resources[id]->getSize(address));
	}
	else { //not found
		return 0;
	}
}

int WebContent_List::getChunk(QString url, char* buffer, quint64 start, int len)
{
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);
	
	qDebug() << identifier << ": fetching data from url " << url;

	if (url == "") { //the resource is this list itself
		
		if (start <= content.length()) {
			size_t real_len = content.length() - start;
			if (len < real_len) {
			  real_len = len;
			}
			memcpy(buffer, content.mid(start,real_len).constData(), real_len);
			return real_len; //OK
		}
		return -1;
	}
	else if (resources.contains(id)) { 
		return (resources[id]->getChunk(address, buffer, start, len));
	}
	else { //not found
		return -1;
	}
}

bool WebContent_List::validUrl(QString url) {
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);
	
	qDebug("ID: ");
	qDebug() << id;
	//qDebug(id.data()->);
	
	qDebug("address: ");
	qDebug() << address;
	//qDebug(address);
	
	if (id.isEmpty()) { //the resource is this list itself
		return true;
	}
	else if (resources.contains(id)) {
		return (resources[id]->validUrl(address));
	}
	else { //not found
		return false;
	}
}

void WebContent_List::updateCache() {
	content.clear();
	
	QTextStream stream(&content);
	stream << "<html>\n<head>\n<title>List</title>\n</head>\n";
	stream << "<body>\n";
	
	stream << "<ul>\n";
	foreach(QString key, resources.keys()) {
		stream << "<li><a href='" << resources[key]->getUrl() << "'>" << key << "</li>\n";
	}

	stream << "</ul>\n";
	stream << "</body>\n</html>";
	stream.flush();
}

