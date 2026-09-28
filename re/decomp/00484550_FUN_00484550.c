// FUN_00484550 @ 00484550 size=49 sig=undefined FUN_00484550() cc=unknown
// callers: FUN_004845b8
// callees: 

longlong FUN_00484550(char *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*param_1 != '\0') {
    iVar1 = 1;
  }
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if (*param_1 == '\n') {
      iVar1 = iVar1 + 1;
    }
  }
  return (longlong)(DAT_0065e010 + 1) * (longlong)iVar1;
}

