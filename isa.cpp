#include "isa.h"



std::list<std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string>> ISA = {
    {"add", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000100000"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sub", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000100010"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"and", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000100100"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"or", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000100101"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"xor", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000100110"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sge", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000101101"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sle", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000101100"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sll", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000100"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sne", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000101001"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"srl", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000110"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"xnor", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000001"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"nand", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000010"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"nor", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000011"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"slt", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000101"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sgt", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000000111"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"seq", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000001000"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"sra", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000001001"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"rol", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000001010"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},
    {"ror", RTYPE, std::bitset<6>(RTYPE_OP), std::bitset<11>("00000001011"), GENERIC_RTYPE, GENERIC_RTYPE_FORMAT},

    {"addi", IMMEDIATE, std::bitset<6>("001000"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"subi", IMMEDIATE, std::bitset<6>("001010"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"andi", IMMEDIATE, std::bitset<6>("001100"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"ori", IMMEDIATE, std::bitset<6>("001101"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"xori", IMMEDIATE, std::bitset<6>("001110"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"beqz", IMMEDIATE, std::bitset<6>("000100"), std::bitset<11>(IMMEDIATE_OP), BRANCH_IMMEDIATE, BRANCH_IMMEDIATE_FORMAT},
    {"bnez", IMMEDIATE, std::bitset<6>("000101"), std::bitset<11>(IMMEDIATE_OP), BRANCH_IMMEDIATE, BRANCH_IMMEDIATE_FORMAT},
    {"lw", IMMEDIATE, std::bitset<6>("100011"), std::bitset<11>(IMMEDIATE_OP), LOAD_IMMEDIATE, LOAD_IMMEDIATE_FORMAT},
    {"sw", IMMEDIATE, std::bitset<6>("101011"), std::bitset<11>(IMMEDIATE_OP), STORE_IMMEDIATE, STORE_IMMEDIATE_FORMAT},
    {"sgei", IMMEDIATE, std::bitset<6>("011101"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"slei", IMMEDIATE, std::bitset<6>("011100"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"slli", IMMEDIATE, std::bitset<6>("010100"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"snei", IMMEDIATE, std::bitset<6>("011001"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"srli", IMMEDIATE, std::bitset<6>("010110"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"xnori", IMMEDIATE, std::bitset<6>("011110"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"nandi", IMMEDIATE, std::bitset<6>("000001"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"nori", IMMEDIATE, std::bitset<6>("000111"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"slti", IMMEDIATE, std::bitset<6>("001001"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"sgti", IMMEDIATE, std::bitset<6>("001011"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"seqi", IMMEDIATE, std::bitset<6>("001111"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"srai", IMMEDIATE, std::bitset<6>("010000"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"roli", IMMEDIATE, std::bitset<6>("010001"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"rori", IMMEDIATE, std::bitset<6>("010010"), std::bitset<11>(IMMEDIATE_OP), GENERIC_IMMEDIATE, GENERIC_IMMEDIATE_FORMAT},
    {"nop", IMMEDIATE, std::bitset<6>("010101"), std::bitset<11>(IMMEDIATE_OP), NOP_IMMEDIATE, NOP_IMMEDIATE_FORMAT},

    {"j", JUMP, std::bitset<6>("000010"), std::bitset<11>(JUMP_OP), GENERIC_JUMP, GENERIC_JUMP_FORMAT},
    {"jal", JUMP, std::bitset<6>("000011"), std::bitset<11>(JUMP_OP), GENERIC_JUMP, GENERIC_JUMP_FORMAT}
};
