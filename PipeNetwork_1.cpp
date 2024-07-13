#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "Node.hpp"
#include "Tube.hpp"
#include "PipeNetwork.hpp"
#include "linalg.hpp"

namespace cie
{
	namespace pipenetwork
	{
		PipeNetwork::PipeNetwork(const std::string& filename) :
			filename_(filename)
		{

		}

		std::vector<double> PipeNetwork::computeFluxes() const
		{
			std::ifstream infile(filename_);

			int numberofNodes, numberofTubes;

			infile >> numberofNodes;
			infile >> numberofTubes;

			std::map<int, std::vector<double>>nodes;

			int id = 0;

			for (int i = 2; i < numberofNodes + 2; ++i)
			{

				while (id < numberofNodes)
				{
					std::vector<double> node;
					double x, y, flow;
					infile >> x >> y >> flow;

					node.push_back(x);
					node.push_back(y);
					node.push_back(flow);

					nodes[id] = node;
					id++;
				}
			}

			std::map<int, std::vector<double>>tubes;

			int id_t = 0;
			for (int i = 2 + numberofNodes; i < 2 + numberofNodes + numberofTubes; ++i)
			{
				while (id_t < numberofTubes)
				{
					std::vector<double> tube;
					double node1, node2, diameter;
					infile >> node1 >> node2 >> diameter;

					tube.push_back(node1);
					tube.push_back(node2);
					tube.push_back(diameter);

					tubes[id_t] = tube;
					id_t++;
				}
			}


			//initialize zero matrix B			

			using Matrix = linalg::Matrix;

			Matrix B(numberofNodes, numberofNodes);

			std::vector<double> Q(numberofNodes, 0.0);

			for (int i = 0; i < numberofTubes; ++i)
			{
				auto tube_i = tubes.find(i);

				//get the id of the bounding nodes
				int node_id1 = tube_i->second[0];
				int node_id2 = tube_i->second[1];

				auto node1 = nodes.find(node_id1);
				auto node2 = nodes.find(node_id2);

				Node node_1(node1->second[0], node1->second[1], node1->second[2], node1->first);
				Node node_2(node2->second[0], node2->second[1], node2->second[2], node2->first);

				Tube tube(&node_1, &node_2, tube_i->second[2]);

				B(node_id1, node_id1) += tube.permeability(); // the idx starts from 0
				B(node_id2, node_id2) += tube.permeability();
				B(node_id1, node_id2) -= tube.permeability();
				B(node_id2, node_id1) -= tube.permeability();

				Q[node_id1] = -1 * node_1.flow();
				Q[node_id2] = -1 * node_2.flow();

			}

			Matrix B_arr = B;

			for (int i = 0; i < numberofNodes; ++i)
			{
				B(i, 0) = 0;
				B(0, i) = 0;
			}

			B(0, 0) = 1;
			Q[0] = 0;


			std::vector<double> head;

			head = linalg::solve(B, Q);

			std::vector<double> fluxes(numberofTubes, 0.0);

			for (auto it = tubes.begin(); it != tubes.end(); ++it)
			{
				int id1 = it->second[0];
				int id2 = it->second[1];
				int id_t = it->first;
				fluxes[id_t] = -B_arr(id1, id2) * (head[id1] - head[id2]);

			}

			return fluxes;
		}


		std::string& PipeNetwork::filename()
		{
			return filename_;
		}


	} //namespace pipenetwork
} //namespace cie
