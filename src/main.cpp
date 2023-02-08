#include "ncurses_display.h"
#include "system.h"
#include "format.h"
#include "linux_parser.h"
#include<vector>



int main() {
  System system;
  LinuxParser::CpuUtilization();
  NCursesDisplay::Display(system);
}