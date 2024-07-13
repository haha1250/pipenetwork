#include <iostream>
#include <typeinfo>

#include "Node.hpp"
#include "Tube.hpp"
#include "PipeNetwork.hpp"
#include "linalg.hpp"

int main()
{
    cie::pipenetwork::PipeNetwork network("testinput.txt");

    std::cout << "filename is: " << network.filename() << std::endl;
    auto result = network.computeFluxes();
    std::cout << "\n";
    cie::linalg::write(result);
    
}
