#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#ifndef ISA_H_INCLUDED
#define ISA_H_INCLUDED

#include <tuple>
#include <list>
#include <string>
#include <bitset>
#include <array>

#define RTYPE 'r'
#define IMMEDIATE 'i'
#define UIMMEDIATE 'u'
#define JUMP 'j'

#define IMMEDIATE_OP "00000000000"
#define UIMMEDIATE_OP "00000000000"
#define JUMP_OP "00000000000"
#define RTYPE_OP "000000"

#define GENERIC_RTYPE "(r[[:d:]]+,){2}r[[:d:]]+"
#define GENERIC_RTYPE_FORMAT "r%u,r%u,r%u"
#define NOT_RTYPE "r[[:d:]]+,r[[:d:]]+"
#define NOT_RTYPE_FORMAT "r%u,r%u"
#define GENERIC_IMMEDIATE "(r[[:d:]]+,){2}-?[[:d:]]+"
#define GENERIC_IMMEDIATE_FORMAT "r%u,r%u,%d"
#define GENERIC_UIMMEDIATE "(r[[:d:]]+,){2}[[:d:]]+"
#define GENERIC_UIMMEDIATE_FORMAT "r%u,r%u,%u"
#define STORE_IMMEDIATE "-?[[:d:]]+\\(r[[:d:]]+\\),r[[:d:]]+"
#define STORE_IMMEDIATE_FORMAT "%d(r%u),r%u"
#define LOAD_IMMEDIATE "r[[:d:]]+,-?[[:d:]]+\\(r[[:d:]]+\\)"
#define LOAD_IMMEDIATE_FORMAT "r%u,%d(r%u)"
#define STORE_UIMMEDIATE "[[:d:]]+\\(r[[:d:]]+\\),r[[:d:]]+"
#define STORE_UIMMEDIATE_FORMAT "%u(r%u),r%u"
#define LOAD_UIMMEDIATE "r[[:d:]]+,[[:d:]]+\\(r[[:d:]]+\\)"
#define LOAD_UIMMEDIATE_FORMAT "r%u,%u(r%u)"
#define GENERIC_JUMP "-?[[:d:]]+"
#define GENERIC_JUMP_FORMAT "%d"
#define NOP_IMMEDIATE ""
#define NOP_IMMEDIATE_FORMAT ""
#define BRANCH_IMMEDIATE "(r[[:d:]]+,)-?[[:d:]]+"
#define BRANCH_IMMEDIATE_FORMAT "r%u,%d"

#define FORMATS_SIZE 11

//defined as label,type,opcode,func,argument format
extern std::list<std::tuple<std::string,char,std::bitset<6>,std::bitset<11>,std::string,std::string>> ISA;
constexpr std::size_t hasher(std::string_view s){
    const std::string_view FORMATS[FORMATS_SIZE] = {
    GENERIC_RTYPE_FORMAT,
    GENERIC_IMMEDIATE_FORMAT,
    LOAD_IMMEDIATE_FORMAT,
    STORE_IMMEDIATE_FORMAT,
    GENERIC_JUMP_FORMAT,
    NOP_IMMEDIATE_FORMAT,
    BRANCH_IMMEDIATE_FORMAT,
    GENERIC_UIMMEDIATE_FORMAT,
    STORE_UIMMEDIATE_FORMAT,
    LOAD_UIMMEDIATE_FORMAT,
    NOT_RTYPE_FORMAT
    };
    for (size_t i = 0; i < FORMATS_SIZE; i++)
    {
        if (s == FORMATS[i]) {
            return i;
        }
    }
    return SIZE_MAX;
}

#endif // ISA_H_INCLUDED

#pragma clang diagnostic pop