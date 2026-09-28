// DoRiot @ 0046c310 size=233 sig=undefined DoRiot() cc=unknown
// callers: FUN_0046c49c,FUN_0047d49c
// callees: FUN_0044de9c,FUN_00423690,FUN_0046c9d8
// strings: \"DoRiot\"

/* auto-named from string evidence: DoRiot */

void DoRiot(int param_1,short param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  int *piVar5;
  uint local_40 [13];
  uint local_c;
  int local_8;
  
  *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) - param_2;
  local_8 = 0;
  piVar5 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar5;
    if (iVar1 != 0) {
      uVar2 = FUN_0046c9d8(100,s_DoRiot_004d58b6);
      if ((uVar2 <= 100U - (int)*(char *)(param_1 + 0x27) >> 2) && (*(char *)(iVar1 + 4) != 0x26)) {
        FUN_0044de9c(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,(int)*(char *)(iVar1 + 4),
                     (int)*(char *)(param_1 + 0x21),local_40);
        iVar4 = (int)local_40[0] >> 1;
        if (iVar4 < 0) {
          iVar4 = iVar4 + (uint)((local_40[0] & 1) != 0);
        }
        local_c = *(short *)(iVar1 + 0x14) + iVar4;
        if ((int)local_40[0] < (int)local_c) {
          puVar3 = local_40;
        }
        else {
          puVar3 = &local_c;
        }
        *(short *)(iVar1 + 0x14) = (short)*puVar3;
        FUN_00423690((int)*(char *)(param_1 + 0x20),0x53,param_1,
                     *(undefined4 *)(&DAT_004f9dbc + *(char *)(iVar1 + 4) * 0x32),0,0);
      }
    }
    local_8 = local_8 + 1;
    piVar5 = piVar5 + 0xd;
  } while (local_8 < 0x24);
  return;
}

