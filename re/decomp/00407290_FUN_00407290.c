// FUN_00407290 @ 00407290 size=274 sig=undefined FUN_00407290() cc=unknown
// callers: 
// callees: FUN_00444274,FUN_0040526c,FUN_00406dd8,FUN_0045093c

void FUN_00407290(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  
  bVar3 = (byte)param_3;
  if (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < -0x13) {
    if (((-1 < *(int *)(&DAT_005220a4 + param_3 * 4 + param_1 * 0x1c)) &&
        ((1 << (bVar3 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) &&
       ((int)(&DAT_0059f3da)[param_1 * 0xb6 + param_3] <
        (int)(&DAT_0059f3f6)[param_2 * 0xb6 + param_3])) {
      iVar1 = FUN_00444274(param_3);
      iVar2 = FUN_00444274(param_1);
      if (iVar2 < iVar1) {
        FUN_0045093c(param_1,1 << (bVar3 & 0x1f),0xffffffff,9,param_2,0,0);
        return;
      }
    }
    FUN_0040526c(param_1,param_3,0xfffffffc);
  }
  else if (((0x13 < *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c)) &&
           (-1 < *(int *)(&DAT_005220a4 + param_3 * 4 + param_1 * 0x1c))) &&
          ((1 << (bVar3 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) {
    FUN_0040526c(param_1,param_3,4);
    FUN_00406dd8(param_1,param_3);
  }
  return;
}

