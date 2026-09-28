// FUN_0041ff24 @ 0041ff24 size=92 sig=undefined FUN_0041ff24() cc=unknown
// callers: FUN_004213fc,FUN_00420e34,FUN_00420aac,FUN_00449dec,FUN_00448dfc,CheckColonyAssistant,FUN_00421584,FUN_00420d34,FUN_00421340,FUN_004217a0,FUN_00421178,FUN_00421734,FUN_0041fd38,FUN_00421828,FUN_0041ffd4
// callees: FUN_00414ea4,FUN_0049eb44

void FUN_0041ff24(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_004b7a14 != 0) {
    local_10 = 0;
    local_c = 0;
    local_8 = 0x280;
    local_4 = 0x1e0;
    FUN_00414ea4(&local_10);
    FUN_0049eb44(DAT_004b7a14,10,1,8,0,0);
    FUN_0049eb44(DAT_004b7a14,0x4a,1,8,0,0);
  }
  return;
}

