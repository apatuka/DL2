// FUN_0047e2fc @ 0047e2fc size=35 sig=undefined FUN_0047e2fc() cc=unknown
// callers: FUN_00480be0,FUN_00480d78,DrawSTileBuilding
// callees: 

void FUN_0047e2fc(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (param_3 + 2U < 0x19) {
                    /* WARNING: Could not emulate address calculation at 0x0047e30e */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&PTR_LAB_0047e334)[CONCAT31((int3)(param_3 + 2U >> 8),(&DAT_0047e31d)[param_3])])();
    return;
  }
  return;
}

