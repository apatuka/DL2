// FUN_00495086 @ 00495086 size=51 sig=undefined FUN_00495086() cc=unknown
// callers: 
// callees: FUN_0048e3f1,FUN_00495162
// strings: \"Mouse Pos:%d, %d\\r\\n\"

void FUN_00495086(void)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if ((DAT_0051dca4 & 4) != 0) {
    FUN_0048e3f1(&local_8,&local_c);
    FUN_00495162(s_Mouse_Pos__d___d_0051dcac,local_8,local_c);
  }
  return;
}

