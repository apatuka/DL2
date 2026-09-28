// FUN_0040526c @ 0040526c size=266 sig=undefined FUN_0040526c() cc=unknown
// callers: FUN_00484114,FUN_00407248,FUN_00407c2c,FUN_00406c64,FUN_0040350c,FUN_004073e4,FUN_00407290,FUN_00406dd8,FUN_00407864,FUN_004046e8
// callees: FUN_004051c4,FUN_0047549c

void FUN_0040526c(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int local_1c [5];
  int local_8;
  
  iVar1 = FUN_004051c4(param_1,param_2);
  if ((iVar1 == 0) && ((1 << ((byte)param_2 & 0x1f) & *(uint *)(&DAT_00522248 + param_1 * 4)) == 0))
  {
    local_8 = *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) + param_3;
    iVar3 = (int)param_3 >> 1;
    iVar1 = *(int *)(&DAT_00522168 + param_2 * 4 + param_1 * 0x1c);
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((param_3 & 1) != 0);
    }
    local_1c[4] = iVar1 + iVar3;
    local_1c[3] = 0xffffffce;
    local_1c[2] = 0x32;
    if ((int)(*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) + param_3) < 0x33) {
      piVar2 = &local_8;
    }
    else {
      piVar2 = local_1c + 2;
    }
    if (*piVar2 < -0x31) {
      piVar2 = local_1c + 3;
    }
    *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) = *piVar2;
    local_1c[1] = 0xffffffce;
    local_1c[0] = 0x32;
    if (iVar1 + iVar3 < 0x33) {
      piVar2 = local_1c + 4;
    }
    else {
      piVar2 = local_1c;
    }
    if (*piVar2 < -0x31) {
      piVar2 = local_1c + 1;
    }
    *(int *)(&DAT_00522168 + param_2 * 4 + param_1 * 0x1c) = *piVar2;
    *(uint *)(&DAT_00522248 + param_1 * 4) =
         *(uint *)(&DAT_00522248 + param_1 * 4) | 1 << ((byte)param_2 & 0x1f);
    if (DAT_0058f1fc != 0) {
      FUN_0047549c();
    }
  }
  return;
}

