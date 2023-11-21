#include <iostream>

#include "CommonFunctions.h"
#include "ErrorLogger.h"
#include "ResourceManager.h"

namespace Utils
{
ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager _instance;

    return _instance;
}

bool ResourceManager::getTexture(const std::string& filename,
                                 WeakTexPtr& texturePtr)
{
    if (!mapHasKey(m_textures, filename))
    {
        if (!loadTextureFromFile(filename))
        {
            std::string errMsg = "Failed to load file: " + filename;
            ERROR(errMsg);
            return false;
        }
    }

    texturePtr = m_textures[filename];
    return true;
}

bool ResourceManager::getSound(const std::string& filename,
                               WeakSndPtr& soundPtr)
{
    if (!mapHasKey(m_sounds, filename))
    {
        if (!loadSoundFromFile(filename))
        {
            std::string errMsg = "Failed to load file: " + filename;
            ERROR(errMsg);
            return false;
        }
    }

    soundPtr = m_sounds[filename];
    return true;
}

bool ResourceManager::getFont(const std::string& filename, WeakFontPtr& fontPtr)
{
    if (!mapHasKey(m_fonts, filename))
    {
        if (!loadFontFromFile(filename))
        {
            std::string errMsg = "Failed to load file: " + filename;
            ERROR(errMsg);
            return false;
        }
    }

    fontPtr = m_fonts[filename];
    return true;
}

ResourceManager::ResourceManager() : m_textures(), m_sounds(), m_fonts() {}

bool ResourceManager::loadTextureFromFile(const std::string& filename)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename))
    {
        std::string errMsg = "Failed to load Texture from file: " + filename;
        ERROR(errMsg);
        return false;
    }

    if (!m_textures.emplace(filename, std::make_shared<sf::Texture>(tex))
             .second)
    {
        std::string errMsg =
            "Failed to insert Texture into map for filename: " + filename;
        ERROR(errMsg);
        return false;
    }

    return true;
}

bool ResourceManager::loadSoundFromFile(const std::string& filename)
{
    sf::SoundBuffer sndBuf;
    if (!sndBuf.loadFromFile(filename))
    {
        std::string errMsg =
            "Failed to load SoundBuffer from file: " + filename;
        ERROR(errMsg);
        return false;
    }

    if (!m_sounds.emplace(filename, std::make_shared<sf::SoundBuffer>(sndBuf))
             .second)
    {
        std::string errMsg =
            "Failed to insert SoundBuffer into map for filename: " + filename;
        ERROR(errMsg);
        return false;
    }

    return true;
}

bool ResourceManager::loadFontFromFile(const std::string& filename)
{
    sf::Font font;
    if (!font.loadFromFile(filename))
    {
        std::string errMsg = "Failed to load Font from file: " + filename;
        ERROR(errMsg);
        return false;
    }

    if (!m_fonts.emplace(filename, std::make_shared<sf::Font>(font))
             .second)
    {
        std::string errMsg =
            "Failed to insert Font into map for filename: " + filename;
        ERROR(errMsg);
        return false;
    }

    return true;
}

ResourceManager::~ResourceManager() {}
} // namespace Utils