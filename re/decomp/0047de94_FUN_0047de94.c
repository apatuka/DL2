// FUN_0047de94 @ 0047de94 size=67 sig=undefined FUN_0047de94() cc=unknown
// callers: FUN_0047dfdc
// callees: FUN_0047dd58

void FUN_0047de94(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = (undefined2 *)(param_1 + 0x152);
  do {
    *puVar1 = 0x7fff;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x1a;
  } while (iVar2 < 0x24);
  DAT_00655038 = 0x7fff;
  DAT_0065503c = param_3;
  DAT_00655040 = param_1;
  FUN_0047dd58(param_2,0);
  return;
}

