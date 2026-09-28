// FUN_0040774c @ 0040774c size=70 sig=undefined FUN_0040774c() cc=unknown
// callers: FUN_00407c2c,FUN_00407be8
// callees: 

int FUN_0040774c(int param_1,int param_2)

{
  int *piVar1;
  int local_c;
  int local_8;
  
  local_8 = 0;
  if ((param_1 == 1) || (param_1 == 2)) {
    local_8 = param_2 - (&DAT_00522520)[param_1];
  }
  local_c = 0;
  if (local_8 < 1) {
    piVar1 = &local_c;
  }
  else {
    piVar1 = &local_8;
  }
  return *piVar1;
}

