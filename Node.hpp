#pragma once
namespace cie
{
	namespace pipenetwork
	{
		class Node
		{
		public:
			Node();
			Node(double x, double y, double flow, int id);

			double x() const;
			double y() const;
			double flow() const;
			int id() const;

		private:

			double x_;
			double y_;
			double flow_;
			int id_;


		};
	} // namespace pipenetwork
} // namespace cie