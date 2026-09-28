// FUN_00409b58 @ 00409b58 size=228 sig=undefined FUN_00409b58() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0040a14c,FUN_00409964,FUN_00408b58,FUN_0040c538,FUN_0040be04,FUN_00408f58,FUN_00409b28,FUN_0040c74c

void FUN_00409b58(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = (&DAT_0059f2cd)[param_1 * 0x2d8];
  FUN_00408b58(param_1,3,10000,2,100,1);
  FUN_00408f58(param_1,3,0xfffff830,2,0);
  FUN_00408f58(param_1,3,0xfffff448,3,0);
  FUN_00408f58(param_1,3,0xfffff830,4,0);
  FUN_00408f58(param_1,3,0xfffff830,9,0);
  if (*(short *)(&DAT_0055a11e + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) != 0) {
    iVar2 = FUN_00409b28();
    if (iVar2 != 0) {
      iVar3 = FUN_0040c74c(param_1,0x14);
      if (iVar3 == 0) {
        FUN_0040be04(param_1,0xffffffff,0xffffffff,iVar2,0x14,(int)cVar1);
      }
      else {
        iVar4 = FUN_0040c538(iVar3,iVar2,0);
        if (iVar4 != 0) {
          *(int *)(iVar3 + 0x10) = iVar2;
        }
      }
    }
  }
  FUN_00409964(param_1);
  FUN_0040a14c(param_1,3,&DAT_004b6548);
  return;
}

