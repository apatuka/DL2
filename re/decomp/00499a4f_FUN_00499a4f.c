// FUN_00499a4f @ 00499a4f size=184 sig=undefined FUN_00499a4f() cc=unknown
// callers: FUN_00491f47,FUN_00499b9f,FUN_00491efa,FUN_00491e81,FUN_0049e638,FUN_00492036,FUN_00499b07,FUN_0049b43c,FUN_00491fe9,FUN_00491e02
// callees: 

undefined4 FUN_00499a4f(byte param_1,byte param_2,byte param_3,int param_4)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  int local_c;
  uint local_8;
  
  local_8 = 0x7fffffff;
  pbVar2 = (byte *)0x0;
  local_c = 0;
  local_c._0_1_ = 0;
  if (*(short *)(param_4 + 2) != 0) {
    pbVar2 = (byte *)(param_4 + 8);
    for (iVar4 = 0; iVar4 < *(short *)(param_4 + 2); iVar4 = iVar4 + 1) {
      iVar1 = local_c;
      if ((pbVar2[3] & 1) == 0) {
        uVar3 = ((uint)param_1 - (uint)*pbVar2) * ((uint)param_1 - (uint)*pbVar2) * 3 +
                ((uint)param_2 - (uint)pbVar2[1]) * 4 * ((uint)param_2 - (uint)pbVar2[1]) +
                ((uint)param_3 - (uint)pbVar2[2]) * 2 * ((uint)param_3 - (uint)pbVar2[2]);
        if ((int)uVar3 < 0) {
          uVar3 = ~uVar3 + 1;
        }
        if ((int)uVar3 < (int)local_8) {
          local_c._0_1_ = (undefined1)iVar4;
          iVar1 = iVar4;
          local_8 = uVar3;
          if (uVar3 == 0) break;
        }
      }
      local_c = iVar1;
      pbVar2 = pbVar2 + 4;
    }
  }
  return CONCAT31((int3)((uint)pbVar2 >> 8),(undefined1)local_c);
}

