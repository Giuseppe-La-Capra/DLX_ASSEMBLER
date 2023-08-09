#include <iostream>
#include <fstream>
#include <regex>
#include "preprocessor.h"
#include "isa.h"
#include "assembler.h"

using namespace std;


void convert(const string & original_filename) noexcept;

int main(int argc, char ** argv)
{
    string original_filename;
    char selection;

    while (true)
    {
        cout << "enter filename to start conversion: ";
        getline(cin,original_filename);
        convert(original_filename);
        cout << "continue with a new conversion?(y/n): ";
        cin >> selection;
        cin.ignore();
        if (selection != 'y'){
            break;
        }
    }
    
    
    return 0;
}


void convert(const string & original_filename) noexcept{
    string temp_filename = "temp_file.txt";
    string temp_filename2 = "temp_file2.txt";
    string output_filename = "output.asm.mem";
    std::map<std::string,int> labels;

    fstream original_file(original_filename, ios_base::in);
    if (!original_file.is_open()){
        cerr << "error, could not open file: " << original_filename << endl;
        return;
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
        return;
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
        return;
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
        return;
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
}