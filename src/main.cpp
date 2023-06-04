#include <cstdio>
#include <iostream>
#include <fstream>
#include <exception>
#include <unistd.h>
#include "ast.hpp"
#include "codegen.hpp"

using namespace std;

extern int yyparse();
extern AST::Program* Root;

int main(int argc, char* argv[]) {

    bool outputGraph = false; // -v
    bool optionError = false;

    string outputfile = "a.out";
    char optimizationLvl = '2';
    string llcOptions = "-O2";

    int optch = ' ';
    while ((optch = getopt(argc, argv, "vo:O::")) != -1) {
        switch (optch) {
            case 'v':
                outputGraph = true;
                break;
            case 'o':
                outputfile = string(optarg);
                break;
            case 'O':
                if (strlen(optarg) != 1 || ((optarg[0] < '0' || optarg[0] > '3') && optarg[0] != 's' && optarg[0] != 'z')) {
                    cerr << "Optimizaion level option should be [-O0, -O1, -O2, -O3, -Os or -Oz], not '-O" << optarg << "'." << endl;
                    optionError = true;
                    break;
                }
                optimizationLvl = optarg[0];
            case '?': default:
                cerr << "Unknown option -" << (char)optch << endl;
                optionError = true;
        }
        if (optionError) break;
    }

    if (optionError) return 1;
    llcOptions[2] = optimizationLvl;

    if (optind >= argc) {
        cerr << "Please give the source file." << endl;
        return 1;
    }
    if (optind < argc - 1) {
        cerr << "Cannot compile multiple files for now." << endl;
        return 1;
    }

    freopen(argv[optind], "r", stdin);
    yyparse();

    if (outputGraph) {
        // test if graphviz is installed or not
        if(system("command -v dot >/dev/null 2>&1")) {
            cerr << "Graphviz is not found. Not able to generate AST visualization.\n"
                << "You could try: sudo apt-get install graphviz\n";
        } else {
            int counter = 0;
            stringstream ss;
            ss << "digraph tree {\n"
                "fontname = \"times\"\n"
                "fontsize = 12\n"
                "node[shape = record, fontname = \"times\"]\n";
            Root->GenGraphNode(counter, ss);
            ss << "}" << endl;
            std::ofstream dotfile("ast_viz.dot");
            dotfile << ss.str() << endl;
            dotfile.close();
            system("dot ast_viz.dot -T png -o ast_viz.png");
        }
    }

    unique_ptr<CodeGenContext> codeGenContext = make_unique<CodeGenContext>();
    if (!codeGenContext->GenerateIRCode(Root)) {
        cerr << "IR generation aborted." << endl;
        return 1;
    }
    if (!codeGenContext->GenerateExecutable(outputfile, llcOptions)) {
        cerr << "Exetuable building aborted." << endl;
        return 1;
    }

    return 0;
}