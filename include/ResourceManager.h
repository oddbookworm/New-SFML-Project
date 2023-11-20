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

class ResourceManager
{
  public:
    static ResourceManager& getInstance();

    bool getTexture(const std::string& filename, WeakTexPtr& texturePtr);
    bool getSound(const std::string& filename, WeakSndPtr& soundPtr);

  private:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    void operator=(const ResourceManager& rhs) = delete;

    bool loadTextureFromFile(const std::string& filename);
    bool loadSoundFromFile(const std::string& filename);

    std::unordered_map<std::string, TexPtr> m_textures;
    std::unordered_map<std::string, SndPtr> m_sounds;
};
} // namespace Utils

#endif // RESOURCEMANAGER_H