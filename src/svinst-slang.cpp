// references:
// https://github.com/MikePopoloski/slang/blob/61dcad52297ae0350c90d13fd390c5d618caa47d/tools/driver/driver.cpp
// https://github.com/Kuree/kratos/blob/a1e695e402fa680f7b06cff0bf4d572bd3670f7c/src/generator.cc#L25-L70
// https://github.com/Kuree/kratos/blob/a1e695e402fa680f7b06cff0bf4d572bd3670f7c/src/util.cc#L100-L107

#include <iostream>

#include "cxxopts.hpp"

#include "slang/compilation/Compilation.h"
#include "slang/syntax/SyntaxTree.h"
#include "slang/text/SourceManager.h"
#include "slang/diagnostics/DiagnosticEngine.h"
#include "slang/diagnostics/TextDiagnosticClient.h"
#include "slang/parsing/Preprocessor.h"
#include "slang/util/OS.h"

bool is_valid_verilog(const std::vector<std::string> & files,
                      const std::vector<std::string> & defines,
                      const std::vector<std::string> & includes,
                      bool separate) {
    // define user-specified macros
    slang::PreprocessorOptions ppoptions;
    ppoptions.predefines = defines;
    ppoptions.predefineSource = "<command-line>";

    // specify include directories
    // TODO: should addSystemDirectory be used instead?
    slang::SourceManager sourceManager;
    for (const std::string& dir : includes) {
        try {
            sourceManager.addUserDirectory(string_view(dir));
        }
        catch (const std::exception&) {
            slang::OS::print("error: include directory '{}' does not exist\n", dir);
        }
    }

    // read in all of the files
    std::vector<slang::SourceBuffer> buffers;
    for (const std::string& file : files) {
        slang::SourceBuffer buffer = sourceManager.readSource(file);
        if (!buffer) {
            slang::OS::print("error: no such file or directory: '{}'\n", file);
            continue;
        }
        buffers.push_back(buffer);
    }

    // collect all of the options
    slang::Bag options;
    options.set(ppoptions);

    // parse the files
    slang::Compilation compilation(options);
    if (!separate) {
        compilation.addSyntaxTree(slang::SyntaxTree::fromBuffers(buffers, sourceManager, options));
    }
    else {
        for (const slang::SourceBuffer& buffer : buffers)
            compilation.addSyntaxTree(slang::SyntaxTree::fromBuffer(buffer, sourceManager, options));
    }

    // set up diagnostics printing
    slang::DiagnosticEngine diagEngine(*compilation.getSourceManager());
    auto client = std::make_shared<slang::TextDiagnosticClient>();
    client->setColorsEnabled(true);
    diagEngine.addClient(client);

    // walk through all of the diagnostic messages
    auto& diagnostics = compilation.getParseDiagnostics();
    for (auto& diag : diagnostics)
        diagEngine.issue(diag);

    // print out diagnostics
    std::string diagStr = client->getString();
    slang::OS::print("{}", diagStr);

    return diagnostics.empty();
}

int main(int argc, char** argv) {
    cxxopts::Options options("svinst-slang", "Parse module instantiations in SystemVerilog.");

    options
        .add_options()
        ("d,define", "Define", cxxopts::value<std::vector<std::string>>()->default_value(""))
        ("i,include", "Include path", cxxopts::value<std::vector<std::string>>()->default_value(""))
        ("ignore-include", "Ignore any includes", cxxopts::value<bool>()->default_value("false"))
        ("full-tree", "Show the full syntax tree rather than just module instantiation",
         cxxopts::value<bool>()->default_value("false"))
        ("separate", "Treat each file as completely separate, not updating define variables after each file",
         cxxopts::value<bool>()->default_value("false"))
        ("files", "List of files", cxxopts::value<std::vector<std::string>>())
        ("h,help", "Print usage");

    options.parse_positional({"files"});

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    auto files = result["files"].as<std::vector<std::string>>();
    auto defines = result["define"].as<std::vector<std::string>>();
    auto includes = result["include"].as<std::vector<std::string>>();
    auto separate = result["separate"].as<bool>();

    if (is_valid_verilog(files, defines, includes, separate)) {
        std::cout << "Valid :-)" << std::endl;
    } else {
        std::cout << "Invalid :-(" << std::endl;
    }
    return 0;
}