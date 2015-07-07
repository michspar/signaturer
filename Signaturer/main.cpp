// Signaturer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "signaturer.h"

namespace po = boost::program_options;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce this help message")
		("in", po::value<string>(), "path to input file")
		("out", po::value<string>(), "path to output file")
		("bs", po::value<int>(), "block size in kilobytes (1024 Kb default)")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || !vm.count("in") || !vm.count("out")) {
		cout << desc << endl;
		return 1;
	}

	auto blockSizeInKilobytes = vm.count("bs") ? vm["bs"].as<int>() : 1024;
	auto in = vm["in"].as<string>();
	auto out = vm["out"].as<string>();
	signaturer s(blockSizeInKilobytes);

	try
	{
		s.signFile(in, out);

		cout << in << " signature was successfully saved to " << out << endl;
	}
	catch (std::exception ex)
	{
		cout << "failed to save " << in << " signature:" << endl << ex.what() << endl;

		return 2;
	}

	return 0;
}

