#include "FileWatcher.hpp"
#include "ThreadOps.hpp"
#include "Logger.hpp"

namespace DAC {

FileWatcher::FileWatcher(const std::string &filepath,
                         const filewatcherFn &callback, bool allowPrintInfo)
    : m_threadLive(true), m_path(filepath), m_callback(callback),
      m_allowPrintInfo(allowPrintInfo) {

  // Throw a thread that runs until object destruction
  async_RunFuncEachTime(0.5f, &m_threadLive, [&]() { update(); });

  if (m_allowPrintInfo) {
    DacLog_INFO("FILEWATCHER '{}' :: CREATION !", m_path);
  }
}

FileWatcher::~FileWatcher() {

  if (m_allowPrintInfo) {
    DacLog_INFO("FILEWATCHER '{}' :: DESTRUCTION !", m_path);
  }

  m_threadLive = false;
}

bool FileWatcher::fileHasBeenModified() {
  std::fstream f(m_path);

  // Get stream as string
  m_auxContent.clear();
  m_auxContent << f.rdbuf();
  m_auxContentStr = m_auxContent.str();

  // Update ref var if there are any change
  bool modified = m_refContentStr != m_auxContentStr;
  if (modified) {
    m_refContentStr = m_auxContentStr;
  }

  return modified;
}

void FileWatcher::update() {
  if (fileHasBeenModified()) {
    m_callback(std::fstream(m_path));
  }
}

} // namespace DAC
