
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "expression/all.hpp"
#include "statement/all.hpp"
#include "SourceFile.hpp"



int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() == 2)
    {
        SourceFile* sf = new SourceFile();

        if (args[1] == "-")
        {
            sf->makeAbstractSyntaxTree(std::cin);
            sf->genAssembly(std::cout);
        }
        else
        {
            std::ifstream input(args[1]);
            std::ofstream output(args[1] + ".s");
            sf->makeAbstractSyntaxTree(input);
            sf->genAssembly(output);
        }

        delete sf;
    }
    else
    {
        std::cerr << "Usage: " << args[0] << " <source>" << std::endl;
    }

    return 0;
}

