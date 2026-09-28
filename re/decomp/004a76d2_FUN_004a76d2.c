// FUN_004a76d2 @ 004a76d2 size=340 sig=undefined FUN_004a76d2() cc=unknown
// callers: FUN_004a7c1f,FUN_004a86dc
// callees: FUN_004a90cc,@__unlockDebuggerData$qv,@__lockDebuggerData$qv,FUN_004010f9,__assertfail
// strings: \"XX.CPP\"|\"(dtorMask & 0x0080) == 0\"|\"what?\"|\"!\\\"what?\\\"\"

void FUN_004a76d2(undefined4 param_1,undefined4 param_2,byte param_3,code *param_4,uint param_5,
                 int param_6)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  
  uVar6 = 2;
  if (param_6 == 0) {
    uVar6 = 0;
  }
  if ((param_3 & 2) != 0) {
    uVar6 = uVar6 | 0x80;
  }
  iVar3 = FUN_004010f9();
  if (**(int **)(iVar3 + 0xc) != 0) {
    ___lockDebuggerData_qv();
    iVar3 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar3 + 0x10) + 0x14) = 3;
    iVar3 = FUN_004010f9();
    *(code **)(*(int *)(iVar3 + 0x10) + 0x18) = param_4;
    uVar4 = FUN_004a90cc(param_2);
    iVar3 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar3 + 0x10) + 0x28) = uVar4;
    iVar3 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar3 + 0x10) + 0x24) = 0;
    iVar3 = FUN_004010f9();
    pcVar5 = *(char **)(*(int *)(iVar3 + 0x10) + 0x28);
    while ((pcVar5 != (char *)0x0 && (cVar2 = *pcVar5, pcVar5 = pcVar5 + 1, cVar2 != '\0'))) {
      iVar3 = FUN_004010f9();
      piVar1 = (int *)(*(int *)(iVar3 + 0x10) + 0x24);
      *piVar1 = *piVar1 + 1;
    }
    iVar3 = FUN_004010f9();
    *(undefined4 *)(*(int *)(iVar3 + 0x10) + 0x1c) = param_1;
    iVar3 = FUN_004010f9();
    (**(code **)(*(int *)(iVar3 + 0x10) + 0xc))();
    ___unlockDebuggerData_qv();
  }
  if ((param_5 & 0x80) != 0) {
    __assertfail(s__dtorMask___0x0080_____0_0051f2e4,s_XX_CPP_0051f2fd,0x2ab);
  }
  param_5 = param_5 & 7;
  if (param_5 == 1) {
    (*param_4)(param_1,uVar6);
  }
  else if (param_5 == 2) {
    (*param_4)(param_1,uVar6);
  }
  else if (param_5 == 3) {
    (*param_4)();
  }
  else if (param_5 == 5) {
    (*param_4)(param_1,uVar6);
  }
  else {
    __assertfail(s___what___0051f30a,s_XX_CPP_0051f313,0x2d2);
  }
  return;
}

