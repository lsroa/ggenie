#include "logger.h"
#include <chrono>
#include <iostream>
#include <vector>

std::vector<Log> Logger::messages;

std::string getCurrentTime() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  std::string output(30, '\0');
  std::strftime(&output[0], output.size(), "[%H:%M:%S] ",
                std::localtime(&time));
  return output;
}

void Logger::log(const std::string &msg) {
  Log log;
  log.msg = msg;
  log.level = Level::Info;
  log.msg = "LOG:" + getCurrentTime() + RESET + msg;
  std::cout << GREEN + log.msg << std::endl;
  messages.push_back(log);
}

void Logger::err(const std::string &msg) {
  Log log;
  log.msg = msg;
  log.level = Level::Error;
  log.msg = RED + "ERR:" + getCurrentTime() + RESET + msg;
  std::cout << log.msg << std::endl;
  messages.push_back(log);
}
