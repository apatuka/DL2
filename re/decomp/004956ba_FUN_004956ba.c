// FUN_004956ba @ 004956ba size=40 sig=undefined FUN_004956ba() cc=unknown
// callers: FUN_004956e2
// callees: 

undefined4 FUN_004956ba(char *param_1)

{
  undefined4 uVar1;
  
  if ((*param_1 == '-') || (*param_1 == '+')) {
    param_1 = param_1 + 1;
  }
  if ((*param_1 < '0') || ('9' < *param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

