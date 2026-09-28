// FUN_00403f5c @ 00403f5c size=121 sig=undefined FUN_00403f5c() cc=unknown
// callers: 
// callees: FUN_004412d4,FUN_0040be04,FUN_0040c68c

void FUN_00403f5c(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_004412d4(param_3,param_1,2);
  if (iVar2 != 0) {
    cVar1 = (&DAT_0059f1bf)[param_1 * 0x2d8];
    if (*(char *)(param_2 + 0x21) == '\0') {
      iVar2 = FUN_0040c68c(param_3,0xd,param_2);
      if (iVar2 == 0) {
        FUN_0040be04(param_3,0xffffffff,0xffffffff,param_2,0xd,(int)cVar1);
      }
    }
    else {
      iVar2 = FUN_0040c68c(param_3,5,param_2);
      if (iVar2 == 0) {
        FUN_0040be04(param_3,0xffffffff,0xffffffff,param_2,5,(int)cVar1);
      }
    }
  }
  return;
}

