#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "BencodeReader.hpp"
#include "PrettyPrinter.hpp"

#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char** argv) {
	std::string filename = "../../../torrent/sample2.torrent";
	std::ifstream iFile(filename.c_str(), std::ios::in | std::ios::binary);
	BencodeReader decoder;
	std::shared_ptr<BenValues> pItem = decoder.decodeFile(iFile);
	std::shared_ptr<PrintPretty> print = std::make_shared<PrintPretty>();
	print->Print(pItem);

	return 0;
}

