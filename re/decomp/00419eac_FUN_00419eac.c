// FUN_00419eac @ 00419eac size=164 sig=undefined FUN_00419eac() cc=unknown
// callers: FUN_00419f50
// callees: GetKeyState,FUN_0045c384,FUN_00419678,FUN_00418d18,FUN_0045c27c,FUN_00419684

void FUN_00419eac(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  int local_8;
  
  uVar1 = GetKeyState(0x12);
  iVar2 = FUN_0045c27c(param_1,param_2);
  if (iVar2 != 0) {
    pcVar5 = &DAT_00533405;
    local_8 = 0;
    do {
      if (*pcVar5 != '\x01') {
        iVar4 = 0;
        piVar3 = (int *)(pcVar5 + -0x12d);
        do {
          if (((uVar1 & 0x8000) != 0) || (*piVar3 == 1)) {
            DAT_00583d64 = piVar3[1];
            FUN_0045c384(iVar2,0);
          }
          iVar4 = iVar4 + 1;
          piVar3 = piVar3 + 8;
        } while (iVar4 < 10);
      }
      local_8 = local_8 + 1;
      pcVar5 = pcVar5 + 0x146;
    } while (local_8 < 100);
    FUN_00419678();
    FUN_00419684();
    FUN_00418d18();
  }
  return;
}

