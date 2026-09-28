// FUN_0044577c @ 0044577c size=129 sig=undefined FUN_0044577c() cc=unknown
// callers: FUN_00445d30
// callees: FUN_004455fc,DebugMessage
// strings: \"freeArmies[6] is invalid.\"

int FUN_0044577c(int *param_1)

{
  int iVar1;
  
  FUN_004455fc(2);
  iVar1 = DAT_004c515c;
  if ((DAT_004c515c == 0) || (*(int *)(DAT_004c515c + 0x54) == 0)) {
    iVar1 = 0;
  }
  else if ((*(undefined2 **)(DAT_004c515c + 0x54) < &DAT_00645370) ||
          ((undefined2 *)0x651caf < *(undefined2 **)(DAT_004c515c + 0x54))) {
    DebugMessage(s_freeArmies_6__is_invalid__004c52dc);
    iVar1 = 0;
  }
  else {
    DAT_004c515c = *(int *)(DAT_004c515c + 0x54);
    *(undefined4 *)(DAT_004c515c + 0x58) = 0;
    if (*param_1 == 0) {
      *(undefined4 *)(iVar1 + 0x54) = 0;
    }
    else {
      *(int *)(iVar1 + 0x54) = *param_1;
      *(int *)(*param_1 + 0x58) = iVar1;
    }
    *param_1 = iVar1;
    FUN_004455fc(3);
  }
  return iVar1;
}

