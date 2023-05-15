#include "Input.h"
#include "pch.h"

Input::Input(int charSize){
	this->charHeight = charSize;
	this->setFont(FontLoader::getInstance().getFont());
}

void Input::setFont(sf::Font& font) {
	this->textbox.setFont(font);
}
void Input::setFontSize(int size) {
	this->charHeight = size;
	this->textbox.setCharacterSize(this->charHeight);
}
void Input::setPosition(sf::Vector2f pos) {
	sf::FloatRect textBounds = textbox.getLocalBounds();
	sf::FloatRect rectBounds = rect.getLocalBounds();

	sf::Vector2f textPos(((this->image.getLocalBounds().width > 0 && this->textbox.getLocalBounds().width > 0) ? 10+ this->image.getLocalBounds().width : 0) +rect.getPosition().x - (textBounds.width / 2.0f) + (rectBounds.width / 2.0f) - 3,
		rect.getPosition().y - (textBounds.height / 2.0f) + (rectBounds.height / 2.0f) - this->charHeight/4.f);
	textbox.setPosition(textPos);
	rect.setPosition(pos);
	image.setPosition({ pos.x + padding.left, pos.y + padding.top });

	position = pos;
}

void Input::setHoverColor(sf::Color color) {
	this->hoverColor = color;
}

void Input::setBackgroundColor(sf::Color color) {
	this->fillColor = color;
	rect.setFillColor(color);
}
void Input::setOutlineColor(sf::Color color) {
	this->rect.setOutlineColor(color);
}
void Input::setOutlineThickness(int x) {
	this->outlineWidth = x;
	this->rect.setOutlineThickness(x);
}
void Input::setTextColor(sf::Color color) {
	this->textbox.setFillColor(color);
}

void Input::drawTo(sf::RenderTarget& window) {
	window.draw(this->rect);
	window.draw(this->image);
	window.draw(this->textbox);
}

bool Input::isMouseOver(sf::RenderWindow& window){
	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
	bool isOver = mouse.x > position.x && mouse.x < position.x + this->rect.getLocalBounds().width && mouse.y > position.y && mouse.y < position.y + this->rect.getLocalBounds().height;
	
	return isOver;
}

void Input::setSize(sf::FloatRect size) {
	this->rect.setSize({size.width, size.height});
}

void Input::setMargin(Vector4i mar) {
	this->margin = mar;
}
void Input::setPadding(Vector4i pad) {
	this->padding = pad;
	sf::FloatRect size;
	size.width = this->image.getLocalBounds().width + ((this->image.getLocalBounds().width > 0 && this->textbox.getLocalBounds().width >0) ? 10 : 0) + this->padding.left + this->padding.right + this->textbox.getLocalBounds().width;
	size.height = std::max(this->image.getLocalBounds().height, this->textbox.getLocalBounds().height) + this->padding.top + this->padding.bottom;
	setSize(size);
	setPosition(position);
}

void Input::setText(std::string text){
	this->text = text;
	textbox.setString(text);
}
void Input::setFlags(char flags) {
	this->flags = flags;
	setPosition(this->position);
}
void Input::setTexture(sf::Texture& texture) {
	this->image.setTexture(texture);
}
void Input::setImageSize(sf::Vector2f size) {
	this->image.setScale(size.x / this->image.getLocalBounds().width, size.y / this->image.getLocalBounds().height);
}
void Input::setTextOutlineColor(sf::Color color) {
	this->textbox.setOutlineColor(color);
}
void Input::setTextOutlineWidth(int w) {
	this->textbox.setOutlineThickness(w);
}
std::string Input::getText(){
	return this->textbox.getString();
}
void Input::update() {
	if (this->isMouseOver(*Global::window))this->rect.setFillColor(this->hoverColor);
	else this->rect.setFillColor(this->fillColor);
}
Vector4i Input::getMargin() {
	return margin;
}
Vector4i Input::getPadding() {
	return padding;
}

sf::FloatRect Input::getSize()
{
	sf::FloatRect tmp;
	tmp.height = std::max(charHeight, (int)image.getLocalBounds().height) + padding.top + padding.bottom + 2 * outlineWidth;
	tmp.width = image.getLocalBounds().width + textbox.getGlobalBounds().width + padding.left + padding.right + 2 * outlineWidth;

	return tmp;
}
sf::FloatRect Input::getFullSize()
{
	sf::FloatRect tmp;
	tmp.height = std::max(charHeight, (int)image.getLocalBounds().height) + padding.top + padding.bottom + margin.top + margin.bottom + 2 * outlineWidth;
	tmp.width = image.getLocalBounds().width + textbox.getGlobalBounds().width + padding.left + padding.right + margin.left + margin.right + 2 * outlineWidth;

	return tmp;
}
sf::Vector2f Input::getPosition() {
	return this->position;
}