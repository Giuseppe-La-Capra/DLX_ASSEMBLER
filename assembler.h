#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <map>
#include <regex>
#include <exception>
#include <cmath>
#include "isa.h"

int assembler (std::stringstream & error_stream, std::fstream & input_file, std::fstream & output_file);
#endif
