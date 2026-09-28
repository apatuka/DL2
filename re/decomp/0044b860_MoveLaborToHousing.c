// MoveLaborToHousing @ 0044b860 size=149 sig=undefined MoveLaborToHousing() cc=unknown
// callers: FUN_0041db10,FUN_0041d2bc
// callees: DebugMessage,FUN_004023dc,FUN_0044ba18,FUN_00475ce8,FUN_0044ba40
// strings: \"Invalid arguments in MoveLaborToHousing()\"|\"No labor in MoveLaborToHousing()\"

/* auto-named from string evidence: MoveLaborToHousing */

undefined4 MoveLaborToHousing(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    DebugMessage(s_Invalid_arguments_in_MoveLaborTo_004c5f92);
  }
  else if (*(int *)(param_2 + 0x18 + param_3 * 4) < 1) {
    DebugMessage(s_No_labor_in_MoveLaborToHousing___004c5fbc);
  }
  else {
    iVar6 = 0;
    piVar5 = (int *)(param_1 + 0x154);
    do {
      iVar1 = *piVar5;
      if (iVar1 != 0) {
        iVar2 = FUN_0044ba18(iVar1);
        iVar3 = FUN_0044ba40(iVar1);
        if ((iVar2 < iVar3) && (iVar2 = FUN_004023dc(iVar1,0x14), iVar2 != -1)) {
          uVar4 = FUN_00475ce8(param_1,param_2,param_3,iVar1,iVar2);
          return uVar4;
        }
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 0xd;
    } while (iVar6 < 0x24);
  }
  return 0;
}

