#include "Utils.h"
#include <cstdlib>
#include <cstring>
#include <unistd.h>

bool SetClipboardText(std::string_view text) {
  // Try Wayland first (wl-copy)
  if (system("which wl-copy > /dev/null 2>&1") == 0) {
    FILE *pipe = popen("wl-copy", "w");
    if (pipe) {
      size_t written = fwrite(text.data(), 1, text.size(), pipe);
      pclose(pipe);
      if (written == text.size())
        return true;
    }
  }

  // Fallback to X11 (xclip)
  if (system("which xclip > /dev/null 2>&1") == 0) {
    const std::string cmd = "printf '%s' \"" + std::string(text) +
                            "\" | "
                            "xclip -selection clipboard -in 2>/dev/null";

    if (system(cmd.c_str()) == 0)
      return true;
  }

  // Final fallback to temporary file method
  if (system("which xsel > /dev/null 2>&1") == 0) {
    const std::string cmd = "printf '%s' \"" + std::string(text) +
                            "\" | "
                            "xsel --clipboard --input 2>/dev/null";

    return system(cmd.c_str()) == 0;
  }

  return false;
}

bool GetRegexMatches(std::string string, std::regex regex,
                     std::vector<std::string> &matches) {
  std::sregex_iterator iter(string.begin(), string.end(), regex);
  std::sregex_iterator end;

  matches.clear();

  size_t i = 0;
  while (iter != end) {
    matches.push_back(iter->str());
    ++iter;
  }
  return !matches.empty();
}
