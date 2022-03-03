#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include"dsh.h"
int main(int argc, char** argv) {
    char prevCommand[100][101];
    int numCommands = 0;
    char line[100];
    char input;
    int arrow = 0;
    int cursor = 0;
    size_t size=0;
    int Session = 1000;
    int file = 0;
    FILE* Output;
    char phoneHome[10000];
    char SessionFolder[10000];
    struct stat Exists;
    snprintf(phoneHome, 10000,"%s/.dsh",getenv("HOME"));
    

    initscr();
    cbreak();
    noecho();
   // refresh();
    WINDOW *commands = newwin(44, 101, 0, 0);
    keypad(commands, TRUE);
  //  printf("%i\n",test);
    WINDOW *output = newwin(44, 101, 0, 101);
    keypad(output, TRUE);
    dsh_init();
    int testing = 0;
    while(file == 0){
	    snprintf(SessionFolder,10000,"%s/%i",phoneHome,Session);
	    
	    if(stat(SessionFolder,&Exists) == 0 && S_ISDIR(Exists.st_mode)){
		    file = 1;
		    printf("%i\n", Session);
		    refresh();
	    }else{
		    Session--;
	    }
    }
   refresh();
    // box(commands,0,0);
  //  box(output,0,0);
  //  wrefresh(commands);
  mvwprintw(output, 0,0,"Output Below and to the right:");
  mvwprintw(commands,0,0,"Input and Commands Below:");
    mvwprintw(commands, 40, 4, "dsh> ");//print at bottom of screen using mvwprintw
    
   // set up boxes here
  //  refresh();
   // box(output,0,0);
   wrefresh(commands);
   wrefresh(output);
  //  keypad(commands, TRUE);
   // keypad(output, TRUE);
 // printf("%i\n", test);
    while(1){
	 input = wgetch(commands);
	//  printf("%i", input);
//	  refresh();
      //  mvwprintw(commands, 30,4, line);
        if(input == '\n'){
	 // snprintf(line, 100, "%s\n", line);// append char input onto line
	 //  line[cursor] = input;
	  // line[cursor+1] = 0;
	   wclear(output);
	   mvwprintw(output, 0,0,"Output Below and to the right:");
	 //  mvwprintw(commands, 40,8, line);
//	   printf("%s", line);
	   mvwprintw(commands,35-numCommands-1,8,line);
	 // dsh_run(line);
	  strcpy(prevCommand[numCommands],line);
	  line[cursor] = input;
	  dsh_run(line);
//	  add command to prevCommand at location numCommands
//	  update screen by adding commands to the screen as storage
//	  printf("%s", prevCommand[numCommands]);
	  numCommands++;
	//  int i;
//	 memset(line, 0, 100);
	wmove(commands,40,8);
	wclrtoeol(commands);
	 wrefresh(commands);
//	 mvwprintw(commands,35-numCommands,8,line);
	 memset(line,0,100);
	  cursor = 0;
	 arrow = 0;
	 char outputFile[10000];
	 snprintf(outputFile, 10000, "%s/%i.stdout", SessionFolder, numCommands-1);
          Output = fopen(outputFile, "r");
	  if(Output == NULL){
		  printf("sorry bud\n");
	  }else{	  
	  char c[1000];
	  int loop = 0;
	  while((c[loop] = fgetc(Output)) != EOF){
		  mvwprintw(output, 10,0,c);
		  loop++;
	  }
	  wrefresh(output);
	  int q;
	  for(q = 0; q < loop; q++){
		  c[q] = 0;
	  }
	  }
	 fclose(Output);
	}else if(input == 0x07){
//	 shorten string by one by adding 0 where it used to end
//	 use mvwprintw to overwrite old line
//	 printf("hello");
	 cursor--;
//	 printf("%i\n", cursor);
	 line[strlen(line)-1] = 0;
	 mvwprintw(commands, 40, 8, line);
	 wdelch(commands);
         wrefresh(commands);	
//	 mvwprintw(commands,30,8,"BACKSPACE WOOOHOOO");
        }else if(input == 0x03){
		//printf("found ya");
        // use mvwprintf to change to old commands if it exists by checking numCommand
	  if(arrow < numCommands){
		 // strcpy(line, prevCommand[arrow]);
		char* sp = " ";
		mvwprintw(commands, 35-arrow, 7, sp);
		 int j;
		 int m;
		// arrow++;
		 for(j=0; j <= 100; j++){
			   line[j] = prevCommand[arrow][j];
		 }	   //	arrow++;
		 cursor = strlen(line);
		 char* p = "*";
		 wmove(commands,40,8);
		 wclrtoeol(commands);
		mvwprintw(commands, 40,8,line);
		mvwprintw(commands, 34-arrow, 7,p);
	  	wrefresh(commands);
		wmove(commands,40,8+strlen(line));
	  }
	  char OUT[10000];
	//  memset(&OUT, 0, 10000);
	//  snprintf(OUT, 10000, "%s/%i.stdout", SessionFolder, arrow);
	 // Output = fopen(OUT, "r");
  //        if(Output == NULL){
//	  } else{
         // char o[1000];
	 // int loop2 = 0;
	//  while((o[loop2] = fgetc(OUT)) != EOF){
	//	  mvwprintw(output, 10,0,o);
	//	  loop2++;
	 // }
	 // wrefresh(output);
	 // int s;
	 // for(s = 0; s < loop2; s++){
//		  o[s] = 0;
//	  }
//	  }
	 // fclose(Output);
	  arrow++;
	 // mvwprintw(commands, 40,8,prevCommand[arrow-1]);
	 // wrefresh(commands);
	// and update screen with old command
	// also get the output of old command from file and add it to the screen using session value value found before loop this keeps seg faulting uuuuuuuuuggggggggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
        // also highlight text of old command 
	}else if(input == 0x02){
		if(arrow <=  1){
			char* air2 = " ";
			int h;
			memset(line,0,100);
			if(arrow > 0){
			arrow--;
			}
		//	strcpy(line, prevCommand[arrow]);
	//		mvwprintw(commands,40,8,line);
			wmove(commands,40,8);
			wclrtoeol(commands);
		//	wmove(commands,40,8);
			mvwprintw(commands,40,8,line);
			mvwprintw(commands, 34-arrow,7,air2);
			wmove(commands,40,8);
			cursor = 0;
			wrefresh(commands);
		} else{
			arrow--;
			int a;
			for(a = 0;a < 100;a++){
				line[a] = prevCommand[arrow-1][a];
			}
			char* air = " ";
			char* star = "*";
			mvwprintw(commands,34-arrow,7,air);
			mvwprintw(commands,35-arrow,7,star);
	         	cursor = strlen(line);
			wmove(commands,40,8);
		        wclrtoeol(commands);
			mvwprintw(commands, 40,8,line);
			wrefresh(commands);
		}
	}else{
	  // printf("%i\n", input); 
           line[cursor] = input;
	   line[cursor+1] = 0;
	   mvwprintw(commands,40,8,line);
	   wrefresh(commands);
	 //snprintf(line, 100, "%s%c", line, input);// append like normal
           cursor++;
	  // update screen using mvwprintw
        }
	
        //empty input just in case
       // dsh_run(line);
      //making minor change here to be able to commit 
       // printf("dsh> ");
   }
}// I have everything implemented correctly except for showing the outputs of old commands when they are scrolled to.
