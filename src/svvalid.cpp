#include <iostream>

#include "slang/compilation/Compilation.h"
#include "slang/syntax/SyntaxTree.h"
#include "slang/text/SourceManager.h"

bool is_valid_verilog(const std::string &src) {
    slang::SourceManager source_manager;
    slang::Compilation compilation;
    auto tree = slang::SyntaxTree::fromText(src, source_manager);
    compilation.addSyntaxTree(tree);
    auto &diagnostics = compilation.getParseDiagnostics();
    return diagnostics.empty();
}

int main(int argc, char** argv) {
    if (is_valid_verilog(argv[1])){
        std::cout << "Valid :-)" << std::endl;
    } else {
        std::cout << "Invalid :-(" << std::endl;
    }
    return 0;
}