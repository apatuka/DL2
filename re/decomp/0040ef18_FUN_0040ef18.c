// FUN_0040ef18 @ 0040ef18 size=228 sig=undefined FUN_0040ef18() cc=unknown
// callers: FUN_0040f2e0,FUN_0040e6e4
// callees: FUN_0040edcc,FUN_0040c578,RemoveArmyFromTaskForce,FUN_0040ee34,FUN_00475854,FUN_00401ac0,FUN_00476f24,FUN_0040ec50,FUN_00416d08,FUN_00407d60

void FUN_0040ef18(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  piVar3 = param_1 + 0x11;
  do {
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      if (*param_1 == 1) {
        iVar2 = FUN_0040ee34((int)*(short *)((int)param_1 + 10),iVar1);
        if (iVar2 != 0) {
          RemoveArmyFromTaskForce(iVar1);
          FUN_00475854(iVar1);
          goto LAB_0040efbb;
        }
      }
      if (*(char *)(iVar1 + 7) != '\t') {
        if (*(short *)(iVar1 + 0x28) < 100) {
          iVar2 = FUN_0040ec50(iVar1);
          if (iVar2 != 0) {
            FUN_00401ac0(iVar1,iVar2,0);
            iVar2 = FUN_00416d08(iVar1);
            if (iVar2 != 0) {
              *(undefined1 *)(iVar1 + 0x25) = 0xe;
              FUN_00476f24(iVar1,0);
            }
            goto LAB_0040efbb;
          }
          if (local_8 == 0) {
            local_8 = FUN_0040edcc(iVar1);
          }
        }
        iVar2 = FUN_0040c578(iVar1);
        if (iVar2 != 0) {
          FUN_00401ac0(iVar1,iVar2,0);
        }
      }
    }
LAB_0040efbb:
    local_c = local_c + 1;
    piVar3 = piVar3 + 1;
    if (0xf < local_c) {
      if (local_8 != 0) {
        FUN_00407d60((int)*(short *)((int)param_1 + 10),1,(int)*(short *)((int)param_1 + 0xe),0x23,
                     (int)*(short *)(local_8 + 0x1a),0x12,1);
      }
      return;
    }
  } while( true );
}

