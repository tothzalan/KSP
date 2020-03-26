#include<ncurses.h>
#include<vector>
#include<fstream>
#include<stdio.h>

std::vector<std::string> read_in(std::string filename){
	std::vector<std::string> tmp;
	std::ifstream file;
	file.open(filename);
	std::string line;
	while(std::getline(file,line)){
		tmp.push_back(line);
	}
	return tmp;
}

int main(int argc, char **argv){
	initscr();
	keypad(stdscr,true);
	if(argc < 2){
		addstr("Wrong number of arguments!\n");
	}
	else{
		int index = 1;
		while(index < argc){
			clear();
			std::vector<std::string> lines = read_in(argv[index]);
			for(int i = 0; i <  lines.size(); i++){
				printw(lines[i].c_str());
				printw("\n");
			}
			int inp;
			inp = getch();
			if(inp == KEY_LEFT && index != 1){
				index--;
			}
			if(inp == KEY_RIGHT){
				index++;
			}
		}
	}
	clear();
	printw("End of presentation");
	getch();
	refresh();
	endwin();

	return 0;
}
