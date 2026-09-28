// FUN_0045a038 @ 0045a038 size=130 sig=undefined FUN_0045a038() cc=unknown
// callers: FUN_0045a91c
// callees: BlitSprite8,DebugMessage
// strings: \"Null Road Pointer.\"

void FUN_0045a038(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  
  iVar1 = (param_1 * param_2 * param_3 & 1) + param_4 * 2;
  if (*(int *)(PTR_DAT_004d0348 + iVar1 * 0x10 + 8) == 0) {
    DebugMessage(s_Null_Road_Pointer__004d1bd8);
  }
  else {
    BlitSprite8(*(int *)(PTR_DAT_004d0348 + iVar1 * 0x10 + 8) + (param_3 & 3) * 0x20 +
                (int)*(short *)(PTR_DAT_004d0348 + iVar1 * 0x10 + 4) * ((int)param_3 >> 2) * 0x20,
                param_1,param_2,0x20,0x20,(int)*(short *)(PTR_DAT_004d0348 + iVar1 * 0x10 + 4),0);
  }
  return;
}

