#include "Textbox.h"
#include "pch.h"
void Textbox::inputLogic(int charTyped) {
	if (charTyped != BACKSPACE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == BACKSPACE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textbox.setString(text.str() + "/");
}
void Textbox::deleteLastChar() {
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str() + "/");
}

Textbox::Textbox() {}
Textbox::Textbox(int size, sf::Color color, bool selected) {
	setFontSize(size);
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = selected;
	if (selected) {
		textbox.setString("/");
	}
	else {
		textbox.setString("");
	}
}
Textbox::Textbox(int size, sf::Color color, bool selected, std::string defaultText) {
	textbox.setCharacterSize(size);
	setFontSize(size);
	textbox.setFillColor(color);
	isSelected = selected;
	if (selected) {
		textbox.setString(defaultText + "/");
	}
	else {
		textbox.setString(defaultText);
	}
}

void Textbox::setLimit(bool bLimit) {
	hasLimit = bLimit;
}
void Textbox::setLimit(bool bLimit, int limit) {
	hasLimit = bLimit;
	this->limit = limit;
}
void Textbox::setSelected(bool sel) {
	isSelected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++) {
			newT += t[i];
		}

		textbox.setString(newT);
	}
	else if(this->isSelectable)textbox.setString(text.str() + "/");
	update();
}
void Textbox::setSelectable(bool sel){
	this->isSelectable = sel;
}
std::string Textbox::getText() {
	return text.str();
}
void Textbox::typedOn(sf::Event input) {
	if (isSelected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text.str().length() < limit) {
					this->inputLogic(charTyped);
				}
				else if (charTyped == BACKSPACE_KEY) {
					deleteLastChar();
				}
			}
			else if (charTyped == BACKSPACE_KEY) {
				if (text.str().length())deleteLastChar();
			}
			else {
				this->inputLogic(charTyped);
			}
			update();
		}
	}
}
void Textbox::setFontSize(int size) {
	charHeight = size;
}