#define _USE_MATH_DEFINES

#include "Tube.hpp"
#include <iostream>
#include <cmath>

namespace cie
{
	namespace pipenetwork
	{
		Tube::Tube()
		{
		}

		Tube::Tube(Node* node1, Node* node2, double diameter):
			node1_(node1), node2_(node2), diameter_(diameter)
		{

		}

		double Tube::length() const
		{
			double length_ = std::sqrt(pow((node2_->x() - node1_->x()), 2) + pow((node2_->y() - node1_->y()), 2));
			
			return length_;
		}

		double Tube::permeability() const
		{
			double g = 9.81;
			double v = 1e-6;
			double permeability_ = M_PI * g * pow(diameter_, 4) / (128 * v * Tube::length());

			return  permeability_;
		}

		const Node* Tube::node1() const
		{
			return node1_;
		}

		const Node* Tube::node2() const
		{
			return node2_;
		}

		double Tube::diameter() const
		{
			return diameter_;
		}

	} 
}