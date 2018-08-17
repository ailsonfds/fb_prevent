#ifndef __SHELLUTILS_H__
#define __SHELLUTILS_H__

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "proctree.h"


std::string execmd(char *cmd);

void safe_fork_bomb();

void print_process_num_by_users();

#endif /* __SHELLUTILS_H__ */