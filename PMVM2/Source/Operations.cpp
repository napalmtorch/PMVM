#include "Operations.hpp"
#include "ExecutionUnit.hpp"
#include "Utility/Debugger.hpp"

namespace PMVM
{
    namespace OperationUtil
    {
        const Operation NULL_OP = Operation("", 0, nullptr);

        const Operation& GetByName(std::string name)
        {
            if (name.length() == 0 || name.c_str() == nullptr) { return NULL_OP; }
            for (size_t i = 0; i < ListCount; i++)
            {
                if (List[i].Name == name) { return List[i]; }
            }
            return NULL_OP;;
        }

        bool ValidateArgumentCount(ExecutionUnit* eu)
        {
            size_t count = eu->CurrentOperation.ArgumentCount;
            if (eu->Position + count > eu->Nodes.size()) { return false; }
            for (size_t i = 0; i < count; i++)
            {
                if (eu->Nodes[eu->Position + i + 1].Type == ExecutionNodeType::Instruction) { return false; }
            }
            return true;
        }
    }

    namespace OperationHandlers
    {
        bool Halt(ExecutionUnit* eu)
        {
            eu->Halt();
            return true;
        }

        bool Exit(ExecutionUnit* eu)
        {
            eu->Halt();
            eu->Finished = true;
            return true;
        }

        bool Add(ExecutionUnit* eu)
        {
            if (!OperationUtil::ValidateArgumentCount(eu)) { return false; }
            return true;
        }

        bool PushVariable(ExecutionUnit* eu)
        {
            if (!OperationUtil::ValidateArgumentCount(eu)) { return false; }

            ExecutionNode node_type  = eu->Nodes[eu->Position + 1];
            ExecutionNode node_name  = eu->Nodes[eu->Position + 2];
            ExecutionNode node_value = eu->Nodes[eu->Position + 3];
            Debug::Info("TYPE: %s", node_type.Value);
            Debug::Info("NAME: %s", node_name.Value);
            Debug::Info("VAL:  %s", node_value.Value);

            DataType type = eu->GetDataTypeFromName(node_type.Value);
            int size = 0;
            switch (type)
            {
                case DataType::Boolean: { size = 1; break; }
                case DataType::Integer: { size = 4; break; }
                case DataType::Character: { size = 1; break; }
                case DataType::String: { size = node_value.Value.length() + 1; break; }
                default: { size = 0; break; }
            }

            if (size == 0) { Debug::Error("Invalid type for variable { TYPE:%d SIZE:%d NAME:%s }", (int)type, size, node_name.Value); return false; }
            Variable v = Variable(node_name.Value, type, size);
            eu->Variables.push_back(v);
            Debug::Info("Pushed variable { TYPE:%d SIZE:%d NAME:%s }", (int)type, size, node_name.Value);
            return true;
        }
    }
}