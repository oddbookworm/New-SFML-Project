#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <unordered_map>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

namespace Utils
{
typedef std::shared_ptr<sf::Texture> TexPtr;
typedef std::weak_ptr<sf::Texture> WeakTexPtr;
typedef std::shared_ptr<sf::SoundBuffer> SndPtr;
typedef std::weak_ptr<sf::SoundBuffer> WeakSndPtr;
typedef std::shared_ptr<sf::Font> FontPtr;
typedef std::weak_ptr<sf::Font> WeakFontPtr;

/**
 * @brief Singleton class for loading and caching Textures and SoundBuffers
 */
class ResourceManager
{
  public:
    /**
     * @brief Gets the instance of the ResourceManager singleton
     *
     * @return ResourceManager& a reference to the singleton
     */
    static ResourceManager& getInstance();

    /**
     * @brief Gets a weak pointer to the Texture object loaded from a file
     * already loaded. If it's not already loaded, it attempts to load it.
     *
     * @param filename the name of the file
     * @param texturePtr [out] the weak pointer to point to the Texture
     * @return true if the Texture has successfully loaded from file (either now
     * or previously)
     * @return false otherwise
     */
    bool getTexture(const std::string& filename, WeakTexPtr& texturePtr);

    /**
     * @brief Gets a weak pointer to the SoundBuffer object loaded from a file
     * already loaded. If it's not already loaded, it attempts to load it.
     *
     * @param filename the name of the file
     * @param soundPtr [out] the weak pointer to point to the SoundBuffer
     * @return true if the SoundBuffer has successfully loaded from file (either
     * now or previously)
     * @return false otherwise
     */
    bool getSound(const std::string& filename, WeakSndPtr& soundPtr);

    /**
     * @brief Gets a weak pointer to the Font object loaded from a file
     * already loaded. If it's not already loaded, it attempts to load it.
     *
     * @param filename the name of the file
     * @param fontPtr [out] the weak pointer to point to the Font
     * @return true if the Font has successfully loaded from file (either
     * now or previously)
     * @return false otherwise
     */
    bool getFont(const std::string& filename, WeakFontPtr& fontPtr);

  private:
    /**
     * @brief Private constructor for the singleton design
     */
    ResourceManager();

    /**
     * @brief Private destructor for the singleton design
     */
    ~ResourceManager();

    /**
     * @brief Deleted copy constructor, should not copy singleton
     */
    ResourceManager(const ResourceManager& other) = delete;

    /**
     * @brief Deleted assignment operator, should not assign singleton
     */
    void operator=(const ResourceManager& rhs) = delete;

    /**
     * @brief Attempts to load a Texture from a file and store a shared pointer
     * to the loaded Texture
     *
     * @param filename name of the file to load
     * @return true if successful
     * @return false otherwise
     */
    bool loadTextureFromFile(const std::string& filename);

    /**
     * @brief Attempts to load a SoundBuffer from a file and store a shared
     * pointer to the loaded SoundBuffer
     *
     * @param filename name of the file to load
     * @return true if successful
     * @return false otherwise
     */
    bool loadSoundFromFile(const std::string& filename);

    /**
     * @brief Attempts to load a Font from a file and store a shared
     * pointer to the loaded Font
     *
     * @param filename name of the file to load
     * @return true if successful
     * @return false otherwise
     */
    bool loadFontFromFile(const std::string& filename);

    /* map holding a correlation between filenames and Texture pointers */
    std::unordered_map<std::string, TexPtr> m_textures;

    /* map holding a correlation between filenames and SoundBuffer pointers */
    std::unordered_map<std::string, SndPtr> m_sounds;

    /* map holding a correlation between filenames and Font pointers */
    std::unordered_map<std::string, FontPtr> m_fonts;
};
} // namespace Utils

#endif // RESOURCEMANAGER_H