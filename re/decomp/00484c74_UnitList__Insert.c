// UnitList__Insert @ 00484c74 size=182 sig=undefined UnitList__Insert() cc=unknown
// callers: ProduceUnits
// callees: FUN_004b02a8,DebugMessage,FUN_00484bf0
// strings: \"pThis NULL in UnitList::Insert()\"

/* auto-named from string evidence: UnitList::Insert */

void UnitList__Insert(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 uVar5;
  
  iVar3 = *param_1;
  if ((param_1[1] == 0) || (param_1[1] == *param_1)) {
    uVar5 = 0x34;
    iVar3 = FUN_004b02a8(0x34);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar2 = 0xb;
      do {
        iVar4 = iVar2 * 4;
        iVar2 = iVar2 + -1;
      } while (-1 < iVar2);
      iVar3 = FUN_00484bf0(iVar3,uVar5,*(undefined4 *)(param_2 + iVar4),unaff_ESI,unaff_EBX,
                           unaff_EBP);
    }
    if (*param_1 != 0) {
      *(int *)(iVar3 + 0x30) = *param_1;
    }
    param_1[1] = iVar3;
    *param_1 = iVar3;
  }
  else {
    for (; (iVar3 != 0 && (*(int *)(iVar3 + 0x30) != param_1[1])); iVar3 = *(int *)(iVar3 + 0x30)) {
    }
    if (iVar3 == 0) {
      DebugMessage(s_pThis_NULL_in_UnitList__Insert___00512360);
    }
    else {
      uVar5 = 0x34;
      iVar2 = FUN_004b02a8(0x34);
      if (iVar2 == 0) {
        uVar5 = 0;
      }
      else {
        iVar4 = 0xb;
        do {
          iVar1 = iVar4 * 4;
          iVar4 = iVar4 + -1;
        } while (-1 < iVar4);
        uVar5 = FUN_00484bf0(iVar2,uVar5,*(undefined4 *)(param_2 + iVar1),unaff_ESI,unaff_EBX,
                             unaff_EBP);
      }
      *(undefined4 *)(iVar3 + 0x30) = uVar5;
      *(int *)(*(int *)(iVar3 + 0x30) + 0x30) = param_1[1];
      param_1[1] = *(int *)(iVar3 + 0x30);
    }
  }
  return;
}

