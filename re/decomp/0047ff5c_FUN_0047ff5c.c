// FUN_0047ff5c @ 0047ff5c size=157 sig=undefined FUN_0047ff5c() cc=unknown
// callers: FUN_00480150
// callees: FUN_0047f4ec,DrawSTileBuilding

void FUN_0047ff5c(int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                 undefined1 param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 local_128 [2];
  undefined2 local_126;
  char local_124;
  undefined1 local_123;
  undefined1 local_122;
  undefined1 local_121;
  undefined2 local_120;
  short local_114;
  
  local_126 = 2;
  local_124 = *(char *)(param_1 + 0x1a);
  local_122 = *(undefined1 *)(param_1 + 0x19);
  local_114 = (short)*(char *)(param_1 + 0x1b);
  local_123 = (&DAT_004f9dc3)[local_124 * 0x32];
  local_120 = param_4;
  local_121 = param_5;
  if (local_114 != 0) {
    local_126 = 0x22;
  }
  puVar3 = local_128;
  iVar2 = (int)local_124;
  uVar1 = FUN_0047f4ec(local_128);
  DrawSTileBuilding(param_2,param_3,uVar1,iVar2,puVar3);
  return;
}

