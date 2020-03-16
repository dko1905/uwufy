#include <iostream>
#include <string>
#include <fstream>
#include <istream>

void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);
void uwufy(std::string &input);

void readlineMode();
char getArgs(std::string arg);

void readlineFileMode(std::ifstream &file);

#define MAXLINE 50

int main(int argc, char *argv[]){
	if(argc < 2){
		// If no args are passed use readline mode.
		readlineMode();
	}
	else{
		auto useF = false;
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

bool readlineOrMax(std::istream &is, std::string &output, unsigned int max){	
	output.clear();

	unsigned int currentIndex = 0;
	char c;

	while( (c = is.get()) ){
		output.push_back(c);
		if(currentIndex >= max || c == '\n'){
			return true;
		}
		currentIndex++;
	}
	return false;
}
void readlineMode(){
	for(std::string temp = std::string(); readlineOrMax(std::cin, temp, MAXLINE);){
		uwufy(temp);
		std::cout << temp;
	}
}
void readlineFileMode(std::ifstream &file){
	for(std::string temp = std::string(); readlineOrMax(file, temp, MAXLINE);){
		uwufy(temp);
		std::cout << temp;
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