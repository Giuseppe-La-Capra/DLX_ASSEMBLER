#include <iostream>
#include <fstream>
#include <regex>
#include "preprocessor.h"
#include "isa.h"
#include "assembler.h"

using namespace std;


int main(int argc, char ** argv)
{
    string original_filename;
    string temp_filename = "temp_file.txt";
    string temp_filename2 = "temp_file2.txt";
    string output_filename = "output.asm.mem";
    std::map<std::string,int> labels;

    if (argc == 2) {
        original_filename.assign(argv[1]);

        if (!regex_match(original_filename, regex("^[\\\\/:_.[:alnum:]]+$"), regex_constants::match_any)){
            cerr << original_filename << " is not a valid filename" << endl;
            return -1;
        }
    } else {
        cerr << "error, number of inputs not right" << endl;
        return -1;
    }




    fstream original_file(original_filename, ios_base::in);
    if (!original_file.is_open()){
        cerr << "error, could not open file: " << original_filename << endl;
        return -1;
    }

    fstream temp_file(temp_filename, ios_base::out | ios_base::trunc);
    fstream temp_file2(temp_filename2, ios_base::out | ios_base::trunc);
    fstream output_file(output_filename, ios_base::out | ios_base::trunc);
    if (!temp_file.is_open() || !temp_file2.is_open() || !output_file.is_open()){
        cerr << "error, could not open file: " << temp_filename << endl;
        temp_file2.close();
        temp_file.close();
        output_file.close();
        original_file.close();
        return -1;
    }


    stringstream error_stream;
    int return_preproc = preproc(error_stream,original_file,temp_file, labels);

    //checking for errors 
    if (return_preproc != 0) {
        cout << error_stream.str();
        temp_file2.close();
        temp_file.close();
        output_file.close();
        original_file.close();
        return return_preproc;
    }

    temp_file.close();
    temp_file.open(temp_filename,ios_base::in);

    return_preproc = dependencies_solver(error_stream,temp_file,temp_file2,labels);

    //checking for errors 
    if (return_preproc != 0) {
        cout << error_stream.str();
        temp_file2.close();
        temp_file.close();
        output_file.close();
        original_file.close();
        return return_preproc;
    }

    temp_file2.close();
    temp_file2.open(temp_filename2,ios_base::in);

    return_preproc = assembler(error_stream,temp_file2,output_file);

    if (return_preproc != 0){
        cerr << error_stream.str();
    } else {
        cout << "conversion completed" << endl;
    }

    
    temp_file2.close();
    temp_file.close();
    output_file.close();
    original_file.close();
    return return_preproc;
}
