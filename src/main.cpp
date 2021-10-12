#include <iostream>

#include "application.hpp"

int main(int argc, char** argv)
{
	int ret = 0;

	if (3 != argc)
	{
		std::cout << "Usage " << argv[0] << " directory destFileName\n";
		ret = 1;
	}
	else
	{
		av::Application app;
		app.run(argv[1],argv[2]);
	}
	return ret;
}

