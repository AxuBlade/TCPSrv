#include "flags.h"

void set_flag(int value)  {

  permissionToRunFlag = value;
  
}

short unsigned int get_flag(void)  {

  return permissionToRunFlag;
  
}
