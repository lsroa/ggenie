#include <string>
#include <vector>

#pragma once
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

enum Level { Info, Warning, Error };

struct Log {
  Level level;
  std::string msg;
};

class Logger {
public:
  static std::vector<Log> messages;
  static void log(const std::string &msg);
  static void err(const std::string &msg);
};
