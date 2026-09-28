// FUN_0047b660 @ 0047b660 size=346 sig=undefined FUN_0047b660() cc=unknown
// callers: FUN_0047b834,FUN_0047bebc,FUN_0047b818,FUN_0047b7bc,FUN_0047b8b4,FUN_0047b98c,SendTerritoryData
// callees: memset,FUN_00479050,BroadcastBlockDirect,BroadcastDirect,memcpy

void FUN_0047b660(undefined4 param_1,undefined4 param_2,int param_3,uint param_4)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  undefined1 local_428 [1040];
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  BroadcastDirect(param_1,DAT_0058f1f4,0x45,param_2,(int)param_4 >> 0x10,param_4 & 0xffff,0,0);
  local_8 = param_3;
  local_c = param_4;
  while (0 < (int)local_c) {
    local_10 = 0x400;
    if ((int)local_c < 0x401) {
      puVar2 = &local_c;
    }
    else {
      puVar2 = &local_10;
    }
    memcpy(local_428,local_8,*puVar2);
    memset(&DAT_006541f0,0,0x610);
    local_14 = 0x400;
    if ((int)local_c < 0x401) {
      puVar2 = &local_c;
    }
    else {
      puVar2 = &local_14;
    }
    iVar1 = FUN_00479050(local_428,&DAT_006541f0,*puVar2);
    iVar3 = 0;
    if (0 < iVar1) {
      do {
        BroadcastBlockDirect(param_1,&DAT_006541f0 + iVar3,0x46,0xfe);
        iVar3 = iVar3 + 0x40;
      } while (iVar3 < iVar1);
    }
    local_18 = 0x400;
    if ((int)local_c < 0x400) {
      puVar2 = &local_c;
    }
    else {
      puVar2 = &local_18;
    }
    BroadcastDirect(param_1,DAT_0058f1f4,0x47,0,(int)*puVar2 >> 8 & 0xff,*puVar2 & 0xff,0,0);
    local_8 = local_8 + 0x400;
    local_c = local_c - 0x400;
  }
  BroadcastDirect(param_1,DAT_0058f1f4,0x48,0,0,0,0,0);
  return;
}

