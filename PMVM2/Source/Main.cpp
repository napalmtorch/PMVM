#include <stdlib.h>
#include <iostream>
#include "Utility/Console.hpp"
#include "Utility/Debugger.hpp"
#include "Utility/StringUtil.hpp"
#include "ExecutionNode.hpp"
#include "ExecutionUnit.hpp"
#include <chrono>
#include <time.h>

using namespace std::chrono;

const char* AppName    = "PurpleMoon Virtual Machine";
const char* AppVersion = "0.1";

int main()
{
    Console::Initialize();
    Debug::Enabled = true;    
    Debug::WriteLineNonFormatted("PurpleMoon Virtual Machine", ConsoleColor::Magenta);
    Debug::WriteLine("Version %s", AppVersion);

    std::vector<PMVM::ExecutionNode> nodes =
    {
        PMVM::ExecutionNode(PMVM::ExecutionNodeType::Instruction, "PUSHVAR"),
        PMVM::ExecutionNode(PMVM::ExecutionNodeType::Type, "INT"),
        PMVM::ExecutionNode(PMVM::ExecutionNodeType::StringLiteral, "TestVar"),
        PMVM::ExecutionNode(PMVM::ExecutionNodeType::DecimalLiteral, "69420"),
        PMVM::ExecutionNode(PMVM::ExecutionNodeType::Instruction, "EXIT"),
    };

    PMVM::ExecutionUnit exec;
    exec.Load(nodes);

    auto start = high_resolution_clock::now();
    exec.Run();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    Debug::WriteLine("Execution time: %f ms", (float)((float)duration.count() / 1000.0f));

    return 0;
}