// FUN_00406c64 @ 00406c64 size=170 sig=undefined FUN_00406c64() cc=unknown
// callers: FUN_00476b8c
// callees: FUN_0046ca40,FUN_00406b1c,FUN_0040526c

int FUN_00406c64(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  
  iVar4 = 0;
  bVar3 = (byte)param_1;
  if ((1 << (bVar3 & 0x1f) & *(uint *)(&DAT_00522264 + param_2 * 4)) == 0) {
    if (((('\x02' < (char)(&DAT_0059f161)[param_2 * 0x2d8]) &&
         (-1 < *(int *)(&DAT_005220a4 + param_1 * 4 + param_2 * 0x1c))) &&
        ((1 << (bVar3 & 0x1f) & *(uint *)(&DAT_0052222c + param_2 * 4)) == 0)) &&
       (iVar1 = FUN_00406b1c(param_2,param_1,param_3,0), iVar1 != 0)) {
      iVar4 = 1;
    }
    if ((iVar4 != 0) || (uVar2 = FUN_0046ca40(), (uVar2 & 1) == 0)) {
      FUN_0040526c(param_2,param_1,4);
    }
    *(uint *)(&DAT_00522264 + param_2 * 4) =
         *(uint *)(&DAT_00522264 + param_2 * 4) | 1 << (bVar3 & 0x1f);
    return iVar4;
  }
  return 0;
}

