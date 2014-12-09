#ifndef IAUNS_ASYNC_FILESYSTEMSYNC_HPP
#define IAUNS_ASYNC_FILESYSTEMSYNC_HPP

#include <vector>
#include "Filesystem.hpp"

namespace CPM_ES_FS_NS {

// Use this system if you want to provide synchronous operations on disk.
// Only used when disk is present.
class FilesystemSync : public Filesystem
{
public:
  FilesystemSync(const std::string& prefix = "")  {mPrefix = prefix;}
  virtual ~FilesystemSync()                       {}

  void update() override;

  void readFile(const std::string& assetName, const FSCallback& cb) override;

private:

  // Vector of assets to load when the system update arrives.
  struct AssetItem
  {
    AssetItem(const std::string& asset, const FSCallback& cb) :
        assetName(asset),
        callback(cb)
    {}

    std::string assetName;
    FSCallback  callback;
  };

  // Assets that are to be loaded.
  std::vector<AssetItem>  mAssets;
  std::string             mPrefix;
};

} // namespace CPM_ES_FS_NS

#endif 
