// FUN_00466ddc @ 00466ddc size=132 sig=undefined FUN_00466ddc() cc=unknown
// callers: FUN_004684d0,FUN_0046878c
// callees: FUN_0042836c,GlobalMemoryStatus,sprintf
// strings: \"This machine has %d megabytes of memory.  You will probably have problems playing with this large a world map. \\n\\nWould you like to go back to select a game with a smaller world?\"|\"Possible memory shortage\"

undefined4 FUN_00466ddc(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  _MEMORYSTATUS local_424;
  undefined1 local_404 [1024];
  
  local_424.dwLength = 0x20;
  GlobalMemoryStatus(&local_424);
  uVar1 = (local_424.dwTotalPhys >> 0x14) + 1;
  if ((uVar1 < 0xc) && (900 < (int)DAT_004d5b1a * (int)DAT_004d5b1b)) {
    sprintf(local_404,PTR_s_This_machine_has__d_megabytes_of_00509830,uVar1);
    iVar2 = FUN_0042836c(PTR_s_Possible_memory_shortage_0050982c,local_404,0x18,0,0);
    if (iVar2 == 1) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

