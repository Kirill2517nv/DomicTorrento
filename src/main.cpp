#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <any>
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
	//print->Print(pItem);
	std::shared_ptr<BenDict> my_dict = std::static_pointer_cast<BenDict>(pItem);
	print->Print(my_dict);
	std::string pole = "created by";
	std::shared_ptr<BenString> my_str = std::make_shared<BenString>(pole);
	std::cout << (*my_dict)[my_str] << std::endl;

	return 0;
}

