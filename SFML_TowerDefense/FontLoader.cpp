#include "FontLoader.h"
#include "pch.h"

FontLoader::FontLoader() {
    if (!m_font.loadFromFile(DEFAULT_FONT)) {
        std::cout << "ERROR::FONTLOADER::CONSTRUCTOR::Failed to load font!\n";
    }
}

FontLoader& FontLoader::getInstance()
{
    static FontLoader instance;
    return instance;
}
sf::Font& FontLoader::getFont() {
    return m_font;
}
