// FUN_00488f76 @ 00488f76 size=41 sig=undefined FUN_00488f76() cc=unknown
// callers: FUN_004393e8,FUN_004988fc
// callees: FUN_00488a09,FUN_004888ec

bool FUN_00488f76(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_004888ec(param_1,0);
  if (iVar1 != -1) {
    FUN_00488a09(iVar1);
  }
  return iVar1 != -1;
}

