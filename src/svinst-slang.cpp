#include <iostream>

#include "cxxopts.hpp"

#include "slang/compilation/Compilation.h"
#include "slang/syntax/SyntaxTree.h"
#include "slang/text/SourceManager.h"
#include "slang/diagnostics/DiagnosticEngine.h"
#include "slang/diagnostics/TextDiagnosticClient.h"
#include "slang/util/OS.h"

bool is_valid_verilog(const std::string &src) {
    slang::SourceManager source_manager;
    slang::Compilation compilation;
    auto tree = slang::SyntaxTree::fromFile(src, source_manager);
    compilation.addSyntaxTree(tree);
    auto &diagnostics = compilation.getParseDiagnostics();

    slang::DiagnosticEngine diagEngine(*compilation.getSourceManager());
    auto client = std::make_shared<slang::TextDiagnosticClient>();
    client->setColorsEnabled(true);
    diagEngine.addClient(client);

    for (auto& diag : compilation.getParseDiagnostics())
        diagEngine.issue(diag);

    std::string diagStr = client->getString();
    slang::OS::print("{}", diagStr);

    return diagnostics.empty();
}

int main(int argc, char** argv) {
    if (argc) {
    }
    if (is_valid_verilog(argv[1])){
        std::cout << "Valid :-)" << std::endl;
    } else {
        std::cout << "Invalid :-(" << std::endl;
    }
    return 0;
}