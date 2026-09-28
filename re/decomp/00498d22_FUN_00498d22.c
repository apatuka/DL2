// FUN_00498d22 @ 00498d22 size=77 sig=undefined FUN_00498d22() cc=unknown
// callers: InitCYGame,FUN_00493564
// callees: FUN_00495162,FUN_00498ccb,GlobalAlloc
// strings: \"Native memory manager memory pool inited.\\r\\n\"

undefined4 * FUN_00498d22(void)

{
  undefined4 *puVar1;
  
  puVar1 = GlobalAlloc(0,0x18);
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  FUN_00498ccb(puVar1);
  if ((DAT_0051dcc4 & 0x10) != 0) {
    FUN_00495162(s_Native_memory_manager_memory_poo_0051e1e0);
  }
  return puVar1;
}

