// UnitList__Delete @ 00484d2c size=123 sig=undefined UnitList__Delete() cc=unknown
// callers: FUN_0044e0a8
// callees: free,DebugMessage
// strings: \"pIterance NULL in UnitList::Delete()\"|\"pThis NULL in UnitList::Delete()\"

/* auto-named from string evidence: UnitList::Delete */

void UnitList__Delete(int *param_1)

{
  int iVar1;
  
  if (param_1[1] == 0) {
    DebugMessage(s_pIterance_NULL_in_UnitList__Dele_00512381);
  }
  else if (param_1[1] == *param_1) {
    *param_1 = *(int *)(param_1[1] + 0x30);
    free(param_1[1]);
    param_1[1] = *param_1;
  }
  else {
    for (iVar1 = *param_1; (iVar1 != 0 && (*(int *)(iVar1 + 0x30) != param_1[1]));
        iVar1 = *(int *)(iVar1 + 0x30)) {
    }
    if (iVar1 == 0) {
      DebugMessage(s_pThis_NULL_in_UnitList__Delete___005123a6);
    }
    else {
      *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(param_1[1] + 0x30);
      free(param_1[1]);
      param_1[1] = iVar1;
    }
  }
  return;
}

