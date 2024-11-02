#include <fstream>
#include <string>

std::string readFile(const char *filePath) {
  std::ifstream file(filePath);
  std::string buffer, line;

  if (file.good()) {
    while (getline(file, line)) {
      buffer += line + "\n";
    }
  }

  file.close();
  return buffer;
}
