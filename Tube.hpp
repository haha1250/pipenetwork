#pragma once
#include "Node.hpp"
namespace cie
{
	namespace pipenetwork
	{
		class Tube
		{
			
		public:
			Tube();
			Tube(Node* node1, Node* node2, double diameter);
			
			double length() const;
			double permeability() const;
			const Node* node1() const;
			const Node* node2() const;
			double diameter() const;

		private:

			const Node* node1_;
			const Node* node2_;
			double diameter_;
		};
	}
}