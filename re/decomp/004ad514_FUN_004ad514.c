// FUN_004ad514 @ 004ad514 size=40 sig=undefined FUN_004ad514() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004ad514(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 - 0x14U < 0x44) {
                    /* WARNING: Could not emulate address calculation at 0x004ad52b */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*(code *)(&PTR_LAB_004ad57c)
                      [CONCAT31((int3)(param_1 - 0x14U >> 8),*(undefined1 *)(param_1 + 0x4ad524))])
                      ();
    return uVar1;
  }
  return 0;
}

