// FUN_00407714 @ 00407714 size=55 sig=undefined FUN_00407714() cc=unknown
// callers: FUN_00407c2c,FUN_00407be8
// callees: 

int FUN_00407714(int param_1,int param_2)

{
  int *piVar1;
  int local_c;
  int local_8;
  
  local_8 = (&DAT_00522520)[param_1] - param_2;
  local_c = 0;
  if ((&DAT_00522520)[param_1] - param_2 < 1) {
    piVar1 = &local_c;
  }
  else {
    piVar1 = &local_8;
  }
  return *piVar1;
}

