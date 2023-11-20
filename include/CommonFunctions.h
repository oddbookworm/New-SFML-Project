#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS

#include <unordered_map>

namespace Utils
{
/**
 * @brief Checks if a std::unordered_map has the given key
 *
 * @tparam _Key Type of the key
 * @tparam _Value Type of the values of the map
 * @param map The map to be checked
 * @param key The key to be checked for
 * @return true if the map has the key
 * @return false if the map does not have the key
 */
template <typename _Key, typename _Value>
bool mapHasKey(const std::unordered_map<_Key, _Value>& map, const _Key& key)
{
    return map.find(key) != map.end();
}
} // namespace Utils

#endif // COMMON_FUNCTIONS