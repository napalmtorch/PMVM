#pragma once
#include <stdlib.h>
#include <string>

namespace PMVM
{
    enum class ExecutionNodeType
    {
        Invalid,
        Instruction,
        Type,
        Variable,

        DecimalLiteral,
        HexLiteral,
        BooleanLiteral,
        CharLiteral,
        StringLiteral,
    };

    class ExecutionNode
    {
        public:
            ExecutionNodeType Type;
            std::string Value;

        public:
            ExecutionNode() : 
                Type(ExecutionNodeType::Invalid), Value(std::string()) { }

            ExecutionNode(ExecutionNodeType type, std::string value) : 
                Type(type), Value(value) { }
    };
}