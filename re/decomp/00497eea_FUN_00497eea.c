// FUN_00497eea @ 00497eea size=186 sig=undefined FUN_00497eea() cc=unknown
// callers: FUN_00498196,FUN_00497fa4
// callees: FUN_0048f869,FUN_0048fade,FUN_0048f992,FUN_0048f877

void FUN_00497eea(int param_1,undefined4 param_2,int param_3,int *param_4)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  undefined2 extraout_var;
  undefined1 local_c [2];
  ushort local_a;
  byte local_7;
  byte local_6;
  byte local_5;
  
  uVar2 = FUN_0048f877(*(undefined4 *)(param_1 + 4));
  if ((uVar2 & 1) != 0) {
    uVar2 = uVar2 + 1;
  }
  if (*param_4 < 0x10) {
    iVar3 = FUN_0048f992(param_2,local_c,8);
    if (iVar3 == 8) {
      pbVar1 = (byte *)(param_3 + *param_4 * 4);
      local_a = FUN_0048f869(CONCAT22(extraout_var,local_a));
      if ((local_6 < local_5) && (local_a != 0)) {
        *pbVar1 = 0;
        if ((local_7 & 2) != 0) {
          *pbVar1 = *pbVar1 | 1;
        }
        pbVar1[1] = (byte)((ulonglong)(((int)(uint)local_a >> 1) + 0x48cd) /
                          (ulonglong)(longlong)(int)(uint)local_a);
        pbVar1[2] = local_6;
        pbVar1[3] = (local_5 - local_6) + 1;
        *param_4 = *param_4 + 1;
      }
      uVar2 = uVar2 - 8;
    }
  }
  if (0 < (int)uVar2) {
    FUN_0048fade(param_2,uVar2,1);
  }
  return;
}

