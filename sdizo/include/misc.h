#ifndef MISC_FUN
#define MISC_FUN
#include <stdint.h>
#include <iostream>
#include <windows.h>

template<typename T, size_t N>
constexpr size_t get_tab_size([[maybe_unused]]T (&tab)[N] ){
	return N;
}
namespace text_colors{
  inline std::ostream& red(std::ostream &s)
  {
      HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
      SetConsoleTextAttribute(hStdout, 
                  FOREGROUND_RED|FOREGROUND_INTENSITY);
      return s;
  }

  inline std::ostream& white(std::ostream &s)
  {
      HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
      SetConsoleTextAttribute(hStdout, 
         FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
      return s;
  }
}
#endif