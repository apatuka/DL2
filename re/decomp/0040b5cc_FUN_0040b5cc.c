// FUN_0040b5cc @ 0040b5cc size=118 sig=undefined FUN_0040b5cc() cc=unknown
// callers: FUN_0040b644
// callees: FUN_0040f794,FUN_00407d60,FindConstructionSite

void FUN_0040b5cc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_8;
  
  local_8 = 0;
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    iVar2 = FindConstructionSite(iVar1,0x1c);
    if ((iVar2 != -1) &&
       (iVar2 = FUN_0040f794((int)*(short *)(param_1 + 10),iVar1,*(undefined4 *)(param_1 + 0x10),
                             param_2), iVar2 != 0)) break;
    piVar3 = (int *)piVar3[1];
    iVar1 = local_8;
  } while (piVar3 != &DAT_00521bb4);
  local_8 = iVar1;
  if (local_8 != 0) {
    FUN_00407d60((int)*(short *)(param_1 + 10),1,(int)*(short *)(param_1 + 0xe),0x1c,
                 (int)*(short *)(local_8 + 0x1a),0,1);
  }
  return;
}

