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

    int optch = ' ';
    while ((optch = getopt(argc, argv, "v")) != -1) {
        switch (optch) {
            case 'v':
                outputGraph = true;
                break;
            case '?': default:
                cerr << "Unknown option -" << (char)optch << endl;
                optionError = true;
        }
    }

    if (optionError) return 1;

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
        int counter = 0;
        stringstream ss;
        ss << "digraph tree {\n"
            "fontname = \"times\"\n"
            "fontsize = 12\n"
            "node[shape = record, fontname = \"times\"]\n";
        Root->GenGraphNode(counter, ss);
        ss << "}" << endl;
        std::ofstream dotfile("graph.dot");
	    dotfile << ss.str() << endl;
        dotfile.close();
    }
    return 0;
}