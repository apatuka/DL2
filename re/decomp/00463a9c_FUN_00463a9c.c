// FUN_00463a9c @ 00463a9c size=79 sig=undefined FUN_00463a9c() cc=unknown
// callers: FUN_00463bcc
// callees: 

int FUN_00463a9c(int *param_1,int param_2,int param_3,short param_4)

{
  short sVar1;
  int iVar2;
  
  if (param_4 == -1) {
    iVar2 = 0;
  }
  else {
    iVar2 = (param_3 + -1) * param_2;
    param_2 = -param_2;
  }
  sVar1 = 0;
  do {
    if (param_3 < sVar1) {
      *param_1 = 0;
    }
    else {
      *param_1 = iVar2;
    }
    param_1 = param_1 + 1;
    iVar2 = iVar2 + param_2;
    sVar1 = sVar1 + 1;
  } while (sVar1 < 0x400);
  return param_2;
}

