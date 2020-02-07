#include <iostream>
#include <string>
#include <fstream>

void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);
void uwufy(std::string &input);

void readlineMode();
char getArgs(std::string arg);

void readlineFileMode(std::ifstream &file);

int main(int argc, char *argv[]){
	if(argc < 2){
		// If no args are passed use readline mode.
		readlineMode();
	}
	else{
		bool useF = false;
		std::string f;
		for(int n = 1; n < argc; n++){
			auto type = getArgs(argv[n]);
			if(type == 'h'){
				std::cout << "Usage:" << std::endl 
					<< "\t-f  --file\tInput file, used to specify input file." << std::endl;
				return 0;
			}
			else if(type == 'f'){
				if(argc > n+1){
					useF = true;
					f = argv[n+1];
				}
				else{
					std::cout << "Missing argument to -f" << std::endl;
				}
			}
		}
		if(useF){
			std::ifstream ifs (f);
			if(ifs.is_open()){
				readlineFileMode(ifs);
			}
			else{
				std::cerr << "Could not open file." << std::endl;
			}
		}
		else{
			std::string arg1 = std::string(argv[1]);
			uwufy(arg1);
			std::cout << arg1;
		}
	}
	
	
}
char getArgs(std::string arg){
	if(arg[0] == '-'){
		if(arg[1] == 'h' || arg.substr(0, 6) == "--help"){
			return 'h';
		}
		else if(arg[1] == 'f' || arg.substr(0, 6) == "--file"){
			return 'f';
		}
	}
	return ' ';
}

void readlineMode(){
	for(std::string line; std::getline(std::cin, line);){
		line.push_back('\n');
		uwufy(line);
		std::cout << line;
	}
}
void readlineFileMode(std::ifstream &file){
	for(std::string line; std::getline(file, line);){
		line.push_back('\n');
		uwufy(line);
		std::cout << line;
	}
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
 
	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}
void uwufy(std::string &input){
	findAndReplaceAll(input, "th", "d");
	findAndReplaceAll(input, "l", "w");
	findAndReplaceAll(input, "r", "w");
	findAndReplaceAll(input, "ohh", "uh");
	findAndReplaceAll(input, "ou", "uw");

	findAndReplaceAll(input, "Th", "D");
	findAndReplaceAll(input, "tH", "d");
	findAndReplaceAll(input, "TH", "D");

	findAndReplaceAll(input, "L", "W");
	findAndReplaceAll(input, "R", "W");
	findAndReplaceAll(input, "Ohh", "Uhh");
}