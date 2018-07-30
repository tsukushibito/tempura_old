#include "temp/asset/asset_common.h"
#include "temp/asset/import.h"
#include "temp/resource/resource_manager.h"

namespace temp {
namespace asset {
class AssetManager : public SmartPointerObject<AssetManager> {
 public:
  AssetManager(const resource::ResourceManager::SPtr& resource_manager,
               const filesystem::path& asset_root);

  void importImage(const filesystem::path& asset_path);

 private:
  resource::ResourceManager::SPtr resource_manager_;
  filesystem::path asset_root_;
};
}  // namespace asset
}  // namespace temp
