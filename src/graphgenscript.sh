flex lexer.l &\
bison -d parser.y &\
g++ main.cpp ast.cpp graphgen.cpp parser.cpp lexer.cpp codegen.cpp utils.cpp -o mcc `llvm-config-12 --libs all --cxxflags --ldflags` &\
./mcc ./testcode/test2.txt -v & dot graph.dot -T png -o graph.png