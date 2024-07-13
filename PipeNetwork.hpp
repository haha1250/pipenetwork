#pragma once
#include "Node.hpp"
#include "Tube.hpp"
#include <string>
#include <vector>

namespace cie
{
	namespace pipenetwork
	{
		class PipeNetwork
		{
		public:
			
			PipeNetwork(const std::string& filename); 
			
			std::vector<double> computeFluxes() const;

			std::string& filename();
			
			
		private:
			std::string filename_;
						
		};
	} //namespace pipenetwork
} //namespace cie