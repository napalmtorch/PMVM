#pragma once
#include <stdlib.h>
#include <string>
#include <vector>
#include "ExecutionNode.hpp"
#include "Operations.hpp"

namespace PMVM
{
    enum class DataType
    {
        Invalid,
        Integer,
        Boolean,
        Character,
        String,
    };

    class Variable
    {
        public:
            std::string Name;
            DataType    Type;
            uint8_t*    Data;
            size_t      Size;

            Variable() : 
                Name(std::string("")), Type(DataType::Invalid), Data(nullptr), Size(0) { }

            Variable(std::string name, DataType type, size_t size) : 
                Name(name), Type(type), Data(nullptr), Size(0) { }
    };

    class ExecutionUnit
    {
        public:
            std::vector<ExecutionNode> Nodes;
            Operation CurrentOperation;

        public:
            std::vector<Variable> Variables;

        public:
            bool     Halted;
            bool     Finished;
            uint32_t Position;

        public:
            void Load(std::vector<ExecutionNode> nodes);
            void Run();

        public:
            void Reset();
            void Halt();
            void Continue();

        public:
            void Step();

        public:
            DataType GetDataTypeFromName(std::string name);
    };
}