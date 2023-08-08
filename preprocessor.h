#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <regex>
#include "isa.h"
#include <cmath>


int preproc (std::stringstream & error_stream, std::fstream & file, std::fstream & processed_tmp_file, std::map<std::string,int> &labels);
int dependencies_solver (std::stringstream & error_stream, std::fstream & proc_file, std::fstream & solved_file, const std::map<std::string,int> &labels);
#endif