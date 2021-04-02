#include<ncurses.h>
#include<vector>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<tuple>

struct Text {
	std::string value;
	attr_t attr;
};

std::tuple<std::string, attr_t> translate(std::string raw_text){
	std::tuple<std::string, attr_t> tmp;
	if(raw_text.length() > 1) {
		if(raw_text.substr(0,1).compare("#") == 0)
			tmp = std::make_tuple(raw_text.substr(1), A_BOLD);
		else if(raw_text.substr(0,1).compare(">") == 0)
			tmp = std::make_tuple(raw_text.substr(1), A_UNDERLINE);
		else if(raw_text.substr(0,1).compare("*") == 0)
			tmp = std::make_tuple("\t->" + raw_text.substr(1), A_DIM);
		else
			tmp = std::make_tuple(raw_text, A_NORMAL);
	}
	else
		tmp = std::make_tuple(raw_text, A_NORMAL);
	return tmp;
}

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
	int row,col;
	getmaxyx(stdscr,row,col);
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
				std::tuple<std::string, attr_t> tmp = translate(lines[i]);
				Text line_txt {std::get<0>(tmp), std::get<1>(tmp)};
				attron(line_txt.attr);
				mvprintw(row/2+i-lines.size(),(col-10)/2,"%s\n",line_txt.value.c_str());
				attroff(line_txt.attr);
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
