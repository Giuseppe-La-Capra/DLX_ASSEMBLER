#include "assembler.h"

static const std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string> & find_op (
    const std::string & buffer 
);
static std::string parse (const std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string> & command,
    const std::string & buffer);


std::string compute_bitset(char type, const std::bitset<6> & opcode, const std::bitset<11> & func,
    const unsigned int & source1, const unsigned int & source2, const unsigned int & dest, const int & immediate);

int assembler (std::stringstream & error_stream, std::fstream & input_file, std::fstream & output_file) {
    int return_value = 0;
    std::string buffer;
    bool found = true;
    std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string> command;
    unsigned long int line = 0;
    do
    {
        std::getline(input_file, buffer);
        found = false;
        //search in ISA for a match 
        if (!buffer.empty()) {
            try
            {
                command = find_op(buffer);
                found = true;
            }
            catch(const std::exception& e)
            {
                error_stream << e.what() << std::endl;
                found = false; //for safety
            }
        
            //if found then write in output file by parsing 
            if (found){
                try
                {
                    buffer = parse(command,buffer);
                }
                catch(const std::exception& e)
                {
                    error_stream << e.what() << std::endl;
                    found = false; //reusing same hella flag boy
                }

                if (found){
                    output_file << buffer << std::endl;
                }
                
            }

            if (!found) {
                //record error line
                error_stream << "error occurred on line " << line << std::endl;
                return_value = -1;
            }
            line++;
        }
        
        
    } while (!input_file.eof());
    
    
    
    return return_value;
}


static const std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string> & find_op (
    const std::string & buffer 
) {
    std::string regex_str;
    for (const auto &i : ISA)
    {
        regex_str = "^" + std::get<0>(i) + " " + std::get<4>(i) + "$";
        if (std::regex_match(buffer,std::regex(regex_str))){
            return i;
        }
    }
    std::string error = "the command \"" + buffer + "\" was not recognized";
    throw std::invalid_argument(error);
}

static std::string parse (const std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string> & command,
    const std::string & buffer) {
    
    std::string format = std::get<0>(command) + " " + std::get<5>(command);
    char type = std::get<1>(command);
    unsigned int dest = 0,source1 = 0,source2 = 0; //registers
    int immediate = 0;

    std::string parsed;
    switch (hasher(std::get<5>(command)))
    {
    case hasher(GENERIC_RTYPE_FORMAT):
        sscanf(buffer.c_str(),format.c_str(),&dest,&source1,&source2);
        break;
    case hasher(GENERIC_IMMEDIATE_FORMAT):
        sscanf(buffer.c_str(),format.c_str(),&dest,&source1,&immediate);
        break;
    case hasher(STORE_IMMEDIATE_FORMAT):
        sscanf(buffer.c_str(),format.c_str(),&immediate,&source1,&dest);
        break;
    case hasher(LOAD_IMMEDIATE_FORMAT):
        sscanf(buffer.c_str(),format.c_str(),&dest,&immediate,&source1);
        break;
    case hasher(GENERIC_JUMP_FORMAT):
        sscanf(buffer.c_str(),format.c_str(),&immediate);
        break;
    default:
        throw std::invalid_argument("internal error parsing: " + buffer );
        break;
    }
    try
    {
        parsed = compute_bitset(type,std::get<2>(command),std::get<3>(command),source1,source2,dest,immediate);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("error parsing: " + buffer + " -> " + e.what());
    }
    
    return parsed;
}

std::string compute_bitset(char type, const std::bitset<6> & opcode, const std::bitset<11> & func,
    const unsigned int & source1, const unsigned int & source2, const unsigned int & dest, const int & immediate) {
    std::stringstream ss;

    std::stringstream error;
    bool error_flag = false;

    if (source1 > 31){
        error << "argument source1 is invalid, it's bigger than 31 " << std::endl;
        error_flag = true;
    }
    if (source2 > 31){
        error << "argument source2 is invalid, it's bigger than 31 " << std::endl;
        error_flag = true;
    }
    if (dest > 31){
        error << "argument dest is invalid, it's bigger than 31 " << std::endl;
        error_flag = true;
    }
    if (error_flag) {
        throw std::invalid_argument(error.str());
    }
    std::bitset<5> rs1(source1),rs2(source2),rd(dest);

    if (type = 'r') {
        ss << opcode.to_string() << rs1.to_string() << rs2.to_string() << rd.to_string() << func.to_string();
        std::bitset<32> fin(ss.str());
        ss.str("");
        ss << std::hex << std::setw(8) << std::setfill('0') << fin.to_ulong();
    } else if (type = 'i') {
        if (-2^15 <= immediate && immediate <= (2^15 -1)){
            std::bitset<16> immediate_bitset(immediate);
            ss << opcode.to_string() << rs1.to_string() << rd.to_string() << immediate_bitset.to_string();
            std::bitset<32> fin(ss.str());
            ss.str("");
            ss << std::hex << std::setw(8) << std::setfill('0') << fin.to_ulong();
        } else {
            throw std::invalid_argument("argument immediate is invalid, it's outside of range");
        }
    } else if (type = 'j') {
        if (-2^25 <= immediate && immediate <= (2^25 -1)){
            std::bitset<26> immediate_bitset(immediate);
            ss << opcode.to_string() << immediate_bitset.to_string();
            std::bitset<32> fin(ss.str());
            ss.str("");
            ss << std::hex << std::setw(8) << std::setfill('0') << fin.to_ulong();
        } else {
            throw std::invalid_argument("argument immediate is invalid, it's outside of range");
        }
    } else {
        throw std::invalid_argument("internal error, instruction type is not defined");
    }

    return ss.str();
}