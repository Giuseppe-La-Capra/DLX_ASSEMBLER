#include "preprocessor.h"


int preproc (std::stringstream & error_stream, std::fstream & file, std::fstream & processed_tmp_file, std::map<std::string,int> &labels) {
    //check if files are open
    if (!file.is_open()) {
        error_stream << "file is not open" << std::endl;
        return -1;
    }

    if (!processed_tmp_file.is_open()) {
        error_stream << "temp file is not open" << std::endl;
        return -1;
    }

    //run preprocessor
    
    std::string buffer = "";
    bool label_flg = false;
    bool instr_flg = false;
    unsigned long int row = 0;
    unsigned long int proc_row = 0;
    std::smatch m;
    std::regex label("^\\s*([[:alpha:]_]+):\\s*$");
    std::regex comment("--.*");
    std::regex instr("^[-,#()[:alnum:][:space:]]+$");
    int return_value = 0;
    do {
        std::getline(file,buffer);
        // removing comments
        buffer = std::regex_replace(buffer,comment,"");
        if (!buffer.empty() && !std::regex_match(buffer,std::regex("^\\s+$"))) {
            // matching label
            label_flg = std::regex_match(buffer,label);
            // matching instr
            instr_flg = std::regex_match(buffer,instr);

            if (label_flg && instr_flg) {
                error_stream << "error on line number " << row << ": line matched both label and instruction in preprocessor" << std::endl;
                error_stream << buffer << std::endl;
                return_value = -1;
            } else if (label_flg && !instr_flg){
                buffer = std::regex_replace(buffer,label,"$1");
                const auto pair_ret = labels.insert({buffer,proc_row});
                if (!pair_ret.second) {
                    error_stream << "error, in row " << row << " the label " << buffer << " was already declared" << std::endl;
                    return_value = -1;
                }
            } else if (!label_flg && instr_flg){
                //keeping only the first whitespace
                std::string temp = buffer;
                bool first = true;
                while (std::regex_search (temp, m, std::regex("([^[:space:]]+)"))) {
                    if (first) {
                        processed_tmp_file << *(m.begin()) << ' ';
                        first = false;
                    } else {
                        processed_tmp_file << *(m.begin());
                    }
                    
                    temp = m.suffix().str();
                }
                // writing buffer in processed file
                processed_tmp_file << '\n';
                proc_row++;
            } else {
                error_stream << "error on line number " << row <<": line did not match any regex in preprocessor" << std::endl;
                error_stream << buffer << std::endl;
            }
        }
        row++;
    } while (!file.eof());
    return return_value;
}


int dependencies_solver (std::stringstream & error_stream, std::fstream & proc_file, std::fstream & solved_file, const std::map<std::string,int> &labels) {

    if (!proc_file.is_open() || !solved_file.is_open()) {
        error_stream << "error, temp files are not open" << std::endl;
        return -1;
    }
    std::string buffer;
    
    std::smatch m;
    int return_value = 0;
    std::string label,operation;
    int pc = 0;
    do
    {
        std::getline(proc_file, buffer);
        pc++;
        std::string temp = buffer;
        bool first = true;
        bool catch_flag = false;


        if (!buffer.empty() && std::regex_match(buffer,std::regex("^([^[:space:]]+)\\s([_[:alpha:]]+)$"))){

            label = std::regex_replace(buffer,std::regex("^([^[:space:]]+)\\s([_[:alpha:]]+)$"),"$2");
            operation = std::regex_replace(buffer,std::regex("^([^[:space:]]+)\\s([_[:alpha:]]+)$"),"$1");

            //try to find a match
            int address;
            catch_flag = false;
            if (!label.empty()){
                // search for a label
                try
                {
                    address = labels.at(label);
                }
                catch(const std::exception& e)
                {
                    error_stream << e.what() << '\n';
                    error_stream << "error, the label " << label << " was not found" << std::endl;
                    error_stream << "error occurred at row " << pc-1 << std::endl;
                    return_value = -1;
                    catch_flag = true;
                }

                

                if (!catch_flag){
                    //resolve address
                    address = address - pc;
                    solved_file << operation << " ";
                    if ((-pow(2.0,25)) <= address && address <= (pow(2.0,25) -1)){
                        solved_file << address;
                    } else {
                        error_stream << "error, label: " << label << " has offset " << address << " at row " << pc-1 << " which is too long on 26 bits" << std::endl;
                        return_value = -1;
                    }
                    solved_file << '\n';
                }
            } else {
                solved_file << buffer << std::endl;
            }
            
        } else {
            if (!buffer.empty()) {
                solved_file << buffer << std::endl;
            } else {
                pc--;
            }
        }
        
    } while (!proc_file.eof());
    return return_value;
}
