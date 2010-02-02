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

#include <QTextStream>
#include <QtDebug>
#include "webcontent_virtualfolder.h"

WebContent_VirtualFolder::WebContent_VirtualFolder(QString identifier) : WebContent(identifier) {
}

bool WebContent_VirtualFolder::addContent(WebContent* content) {
	resources[content->getIdentifier()] = content;
	content->setParent(this);

	//<TODO> should I add some kind of checking here?
	return true;
}

WebContent* WebContent_VirtualFolder::getContent(QString identifier) {
	if (resources.contains(identifier)) {
		return resources[identifier];
	}
	else {
		return NULL;
	}
}

WebContent* WebContent_VirtualFolder::removeContent(QString identifier) {
	if (resources.contains(identifier)) {
		WebContent* buffer = resources[identifier];
		resources.remove(identifier);
		return buffer;
	}
	else {
		return NULL;
	}
}

QString WebContent_VirtualFolder::getMime(QString url) {
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

qint64 WebContent_VirtualFolder::getSize(QString url) {
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

int WebContent_VirtualFolder::getChunk(QString url, QByteArray* buffer, qint64 start, int len)
{
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);

	if (url == "") { //the resource is this list itself
		buffer->clear();
		if (start <= content.length()) {
			buffer->append(content.mid(start, len));
			return content.mid(start, len).size(); //OK
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

bool WebContent_VirtualFolder::validUrl(QString url) {
	QString id;
	QString address;

	id = url.section("/", 0, 0);
	address = url.section("/", 1);

	if (url == "") { //the resource is this list itself
		return true;
	}
	else if (resources.contains(id)) {
		return (resources[id]->validUrl(address));
	}
	else { //not found
		return false;
	}
}

void WebContent_VirtualFolder::updateCache() {
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

