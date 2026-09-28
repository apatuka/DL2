// FUN_00497e3a @ 00497e3a size=176 sig=undefined FUN_00497e3a() cc=unknown
// callers: FUN_00497fa4
// callees: FUN_00497d40

void FUN_00497e3a(undefined4 param_1,byte *param_2,int param_3,undefined4 param_4,code *param_5)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short local_6;
  
  sVar2 = *(short *)(param_2 + 2);
  local_6 = *(short *)param_2 >> 3;
  if ((*param_2 & 7) != 0) {
    local_6 = local_6 + 1;
  }
  uVar4 = (int)local_6 * (uint)param_2[8];
  if ((uVar4 & 1) != 0) {
    uVar4 = uVar4 + 1;
  }
  if (param_3 == 0x204d4250) {
    local_6 = *(short *)param_2;
  }
  bVar1 = param_2[8];
  sVar3 = 0;
  if (0 < sVar2) {
    do {
      FUN_00497d40(param_1,DAT_0065ee0c,DAT_0065ee08,param_2,param_3,&param_4,bVar1,local_6,uVar4);
      if (param_5 != (code *)0x0) {
        (*param_5)(3,DAT_0065ee08,(int)sVar3,(int)(short)uVar4,1,8);
      }
      sVar3 = sVar3 + 1;
    } while (sVar3 < sVar2);
  }
  return;
}

