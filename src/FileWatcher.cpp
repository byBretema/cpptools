#include "../incl/FileWatcher.hpp"
#include "../incl/Async.hpp"
#include "../incl/Logger.hpp"

namespace dac {

// ====================================================================== //
// ====================================================================== //
// w/ default ctor the filewatcher is NOT launced directly
// is needed to call "launch()" after define "path" and "callback"
// ====================================================================== //

FileWatcher::FileWatcher()
    : m_launched(false), m_threadLive(true), m_verbose(false) {}

// ====================================================================== //
// ====================================================================== //
// w/ param ctor the filewatcher is launced directly
// w/o call "launch()"
// ====================================================================== //

FileWatcher::FileWatcher(const std::string&   filepath,
                         const filewatcherFn& callback, bool verbose)
    : m_launched(false), m_threadLive(true), m_verbose(verbose), m_path(""),
      m_callback(nullptr) {
  launch(filepath, callback);
}

// ====================================================================== //
// ====================================================================== //
// Destroy the object and kill thread dependent of this object
// ====================================================================== //

FileWatcher::~FileWatcher() {
  m_threadLive = false;
  if (m_verbose) { dInfo("FileWatcher destroyed @ '{}'", m_path); }
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
  if (fileHasBeenModified()) {
    std::fstream fs(m_path);
    m_callback(fs);
  }
}

// ====================================================================== //
// ====================================================================== //
// Launch the thread to active filewatcher
// ====================================================================== //

bool FileWatcher::launch(const std::string& path, const filewatcherFn& fn) {

  if (m_launched) {
    dErr("FileWatcher already active @ '{}'", m_path);
    return true;
  }
  if (path == "") {
    dErr("Undefined path @ FileWatcher");
    return false;
  }
  if (fn == nullptr) {
    dErr("Empty callback @ '{}' FileWatcher", m_path);
    return false;
  }

  m_path       = path;
  m_callback   = fn;
  m_threadLive = true;

  Async::periodic(0.5f, &m_threadLive, [&]() { update(); });
  m_launched = true;

  if (m_verbose) { dInfo("FileWatcher created @ '{}'", m_path); }
  return true;
}

// ====================================================================== //
// ====================================================================== //
// Setter for verbose
// ====================================================================== //

void FileWatcher::verbose(bool newState) { m_verbose = newState; }

} // namespace dac
