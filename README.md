# MCC
Mini C-- Compiler



编译：

```
c++ main.cpp lexer.cpp parser.cpp ast.cpp graphgen.cpp codegen.cpp `llvm-config-12 --cxxflags --ldflags --system-libs --libs all` -std=c++14 -o mcc -DDEBUG
```



运行：

`./mcc a.c -o a`

选项：

- `-o` 指定生成文件名称
- `-v` 生成 AST 图
- `-On` 编译优化选项，`n` 可选的值为 `0, 1, 2, 3`