// TestMemory @ 0046f94c size=262 sig=undefined TestMemory() cc=unknown
// callers: WinMain
// callees: FUN_0042836c,GlobalMemoryStatus,sprintf,memcpy,FUN_00463a74
// strings: \"This machine has %d megabytes of memory.  To improve game performance, we recommend not loading building animations. You may change your mind by changing the 'Force Small Sprites' option in the game options menu.\\n\\nShall we use the reduced sprite set?\"|\"Possible memory shortage\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Memory test / low memory mode decision */

void TestMemory(void)

{
  undefined *puVar1;
  int iVar2;
  undefined **ppuVar3;
  uint uVar4;
  _MEMORYSTATUS local_424;
  undefined1 local_404 [1024];
  
  local_424.dwLength = 0x20;
  GlobalMemoryStatus(&local_424);
  uVar4 = (local_424.dwTotalPhys >> 0x14) + 1;
  if (uVar4 < 0xc) {
    DAT_004d5994 = 1;
  }
  if ((_DAT_004d5aa4 != 0) || ((uVar4 < 0xc && (1 < DAT_004ed300)))) {
    if (_DAT_004d5aa4 == 0) {
      memcpy(&DAT_0051a8cc,&DAT_0051accc,0x3b0);
      FUN_00463a74();
      sprintf(local_404,PTR_s_This_machine_has__d_megabytes_of_00509828,uVar4);
      iVar2 = FUN_0042836c(PTR_s_Possible_memory_shortage_00509824,local_404,0x18,0,0);
      if (iVar2 == 1) {
        _DAT_004d5aa4 = 1;
      }
      else {
        _DAT_004d5aa4 = 0;
      }
    }
    if (_DAT_004d5aa4 != 0) {
      iVar2 = 0;
      ppuVar3 = &PTR_DAT_004d5b44;
      do {
        puVar1 = *ppuVar3;
        while (*(short *)(puVar1 + 0x14) != 0) {
          *(undefined2 *)(puVar1 + 0x14) = 0;
          *(undefined2 *)(puVar1 + 0x16) = 0;
          puVar1 = puVar1 + 0x10;
        }
        iVar2 = iVar2 + 1;
        ppuVar3 = ppuVar3 + 1;
      } while (iVar2 < 0x34);
    }
  }
  if (DAT_004ed300 == 0) {
    DAT_004d5990 = 1;
  }
  return;
}

