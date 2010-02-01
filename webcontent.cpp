#include "webcontent.h"

WebContent::WebContent(QString identifier) {
	this->identifier = identifier;
	this->parent = NULL;
}

QString WebContent::getUrl() {
	if (parent == NULL) {
		return "";
	}
	else {
		return parent->getUrl() + "/" + identifier;
	}
}
