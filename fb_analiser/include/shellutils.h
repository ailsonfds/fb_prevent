#ifndef __SHELLUTILS_H__
#define __SHELLUTILS_H__

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

std::string execmd(char *cmd);

void safe_fork_bomb();

#endif /* __SHELLUTILS_H__ */