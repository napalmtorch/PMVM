#include "ExecutionUnit.hpp"
#include "Operations.hpp"
#include "Utility/Debugger.hpp"
#include "Utility/StringUtil.hpp"

namespace PMVM
{
    void ExecutionUnit::Load(std::vector<ExecutionNode> nodes)
    {
        Variables.clear();

        // copy nodes
        Nodes.clear();
        for (size_t i = 0; i < nodes.size(); i++) { Nodes.push_back(nodes[i]); }

        // reset state
        Reset();
    }

    void ExecutionUnit::Run()
    {
        Continue();
        while (!Finished)
        {
            if (!Halted)
            {
                Step();
            }
        }
    }

    void ExecutionUnit::Reset()
    {
        Position = 0;
        Finished = false;
        Halted = true;
    }

    void ExecutionUnit::Halt()
    {
        Halted = true;
    }

    void ExecutionUnit::Continue()
    {
        Halted = false;
    }

    void ExecutionUnit::Step()
    {
        if (Position >= Nodes.size()) { Debug::Error("Node pointer out of bounds"); Finished = true; return; }
        ExecutionNode node = Nodes[Position];
        if (node.Type != ExecutionNodeType::Instruction) { Debug::Error("Tried to execute non-instruction node"); Finished = true; return; }

        CurrentOperation = OperationUtil::GetByName(node.Value);
        if (CurrentOperation.Execute == nullptr) { Debug::Error("Invalid instruction"); Finished = true; return; }

        if (!CurrentOperation.Execute(this)) { Debug::Error("Exception while executing operation '" + CurrentOperation.Name + "'"); Finished = true; return; }

        Position += CurrentOperation.ArgumentCount + 1;
        Debug::OK("Executed '" + CurrentOperation.Name + "'");
    }

    DataType ExecutionUnit::GetDataTypeFromName(std::string name)
    {
        std::string n = StringUtil::ToUpper(name);

        if (n == "INT") { return DataType::Integer; }
        if (n == "BOOL") { return DataType::Boolean; }
        if (n == "CHAR") { return DataType::Character; }
        if (n == "STRING") { return DataType::String; }
        return DataType::Invalid;
    }
}