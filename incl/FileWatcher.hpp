#pragma once

#include <fstream>
#include <sstream>
#include <functional>

namespace dac {

class FileWatcher {

  using filewatcherFn = std::function<void(std::fstream)>;

private:
  std::string       m_refContentStr;
  std::string       m_auxContentStr;
  std::stringstream m_auxContent;

  bool m_launched;
  bool m_threadLive;
  bool m_allowPrintInfo;

  std::string   m_path;
  filewatcherFn m_callback;

  // Verify if a file was modified since last time that was loaded
  bool fileHasBeenModified();

  // If file has been modified trigger the stored callback function
  void update();


public:
  // w/ default ctor the filewatcher is NOT launced directly
  // is needed to call "launchWatcher()" after define "path" and "callback"
  FileWatcher();

  // w/ param ctor the filewatcher is launced directly
  // w/o call "launchWatcher()"
  FileWatcher(const std::string& filepath, const filewatcherFn& callback,
              bool allowPrintInfo = true);

  // Destroy the object and kill thread dependent of this object
  ~FileWatcher();

  // Launch the thread to active filewatcher
  void launchWatcher();

  // Set the file path to watch
  void path(const std::string& path);

  // Set the function to run on file change
  void callback(const filewatcherFn& fn);
};

} // namespace dac
