#pragma once
#include <stdlib.h>
#include "ExecutionNode.hpp"

namespace PMVM
{
    class ExecutionUnit;

    class Operation
    {
        public:
            std::string Name;
            size_t ArgumentCount;
            bool (*Execute)(ExecutionUnit*);

            Operation() : 
                Name(std::string("")), Execute(nullptr) { }

            Operation(std::string name, int arg_count, bool (*exec)(ExecutionUnit* eu)) : 
                Name(name), ArgumentCount(arg_count), Execute(exec) { }
    };

    namespace OperationHandlers
    {
        bool Halt(ExecutionUnit* eu);
        bool Exit(ExecutionUnit* eu);
        bool Add(ExecutionUnit* eu);
        bool PushVariable(ExecutionUnit* eu);
    }

    namespace OperationUtil
    {
        static const Operation Halt                 = Operation("HALT", 0, OperationHandlers::Halt);
        static const Operation Exit                 = Operation("EXIT", 0, OperationHandlers::Exit);
        static const Operation Add                  = Operation("ADD", 2, OperationHandlers::Add);
        static const Operation PushVariable         = Operation("PUSHVAR", 3, OperationHandlers::PushVariable);

        static const size_t ListCount = 256;
        static const Operation List[ListCount] = 
        {
            Halt,
            Exit,
            Add,
            PushVariable,
        };

        const Operation& GetByName(std::string name);
        bool ValidateArgumentCount(ExecutionUnit* eu);
    }
}