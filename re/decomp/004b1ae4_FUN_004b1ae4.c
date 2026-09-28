// FUN_004b1ae4 @ 004b1ae4 size=81 sig=undefined FUN_004b1ae4() cc=unknown
// callers: 
// callees: 

void FUN_004b1ae4(int *param_1,int *param_2)

{
  byte bVar1;
  
  if ((*(char *)*param_2 == '\\') && (((char *)*param_2)[1] == '\"')) {
    *(undefined1 *)*param_1 = 0x22;
    *param_2 = *param_2 + 2;
  }
  else {
    bVar1 = *(byte *)*param_2;
    if ((((&DAT_0069f56d)[bVar1] & 4) != 0) && (((byte *)*param_2)[1] != 0)) {
      *(byte *)*param_1 = bVar1;
      *param_2 = *param_2 + 1;
      *param_1 = *param_1 + 1;
    }
    *(undefined1 *)*param_1 = *(undefined1 *)*param_2;
    *param_2 = *param_2 + 1;
  }
  *param_1 = *param_1 + 1;
  return;
}

