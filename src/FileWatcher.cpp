#include "FileWatcher.hpp"
#include "Async.hpp"
#include "Logger.hpp"

namespace dac {

// ====================================================================== //
// ====================================================================== //
// w/ default ctor the filewatcher is NOT launced directly
// is needed to call "launchWatcher()" after define "path" and "callback"
// ====================================================================== //
FileWatcher::FileWatcher()
    : m_launched(false), m_threadLive(true), m_allowPrintInfo(true) {}

// ====================================================================== //
// ====================================================================== //
// w/ param ctor the filewatcher is launced directly
// w/o call "launchWatcher()"
// ====================================================================== //

FileWatcher::FileWatcher(const std::string&   filepath,
                         const filewatcherFn& callback, bool allowPrintInfo)
    : m_launched(false), m_threadLive(true), m_allowPrintInfo(allowPrintInfo),
      m_path(filepath), m_callback(callback) {
  launchWatcher();
}

// ====================================================================== //
// ====================================================================== //
// Destroy the object and kill thread dependent of this object
// ====================================================================== //

FileWatcher::~FileWatcher() {
  m_threadLive = false;
  if (m_allowPrintInfo) { dlog::info("FileWatcher destroyed @ '{}'", m_path); }
}


// ====================================================================== //
// ====================================================================== //
// Verify if a file was modified since last time that was loaded
// ====================================================================== //

bool FileWatcher::fileHasBeenModified() {
  std::fstream f(m_path);

  // Get stream as string
  m_auxContent.clear();
  m_auxContent << f.rdbuf();
  m_auxContentStr = m_auxContent.str();

  bool modified = m_refContentStr != m_auxContentStr;
  // Avoid copy if not needed
  if (modified) { m_refContentStr = m_auxContentStr; }
  return modified;
}

// ====================================================================== //
// ====================================================================== //
// If file has been modified trigger the stored callback function
// ====================================================================== //

void FileWatcher::update() {
  if (fileHasBeenModified()) { m_callback(std::fstream(m_path)); }
}

// ====================================================================== //
// ====================================================================== //
// Launch the thread to active filewatcher
// ====================================================================== //

void FileWatcher::launchWatcher() {

  if (m_launched) { dlog::err("FileWatcher already active @ '{}'", m_path); }

  if (m_path == "" && m_callback == nullptr) {
    dlog::err("Empty callback @ '{}' FileWatcher");
    return;
  }

  m_threadLive = true;
  Async::periodic(0.5f, &m_threadLive, [&]() { update(); });
  m_launched = true;

  if (m_allowPrintInfo) { dlog::info("FileWatcher created @ '{}'", m_path); }
}

// ====================================================================== //
// ====================================================================== //
// Set the file path to watch
// ====================================================================== //

void FileWatcher::path(const std::string& path) { m_path = path; }

// ====================================================================== //
// ====================================================================== //
// Set the function to run on file change
// ====================================================================== //

void FileWatcher::callback(const filewatcherFn& fn) { m_callback = fn; }



} // namespace dac
