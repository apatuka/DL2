// FUN_0048baa6 @ 0048baa6 size=55 sig=undefined FUN_0048baa6() cc=unknown
// callers: InitCYGame,FUN_00493564
// callees: FUN_00495162,FUN_0048ba70
// strings: \"Memory Manager inited, max memory: %ul\\r\\n\"

undefined4 FUN_0048baa6(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0048ba70(2);
  if (uVar1 < param_2) {
    uVar2 = 0;
  }
  else {
    if ((DAT_0051dcc4 & 0x10) != 0) {
      FUN_00495162(s_Memory_Manager_inited__max_memor_0051bd90,uVar1);
    }
    uVar2 = 1;
  }
  return uVar2;
}

