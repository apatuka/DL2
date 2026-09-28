// FUN_0041ff98 @ 0041ff98 size=60 sig=undefined FUN_0041ff98() cc=unknown
// callers: CheckColonyAssistant,FUN_00420d34,FUN_00420e34,FUN_0041fd38,FUN_00420734,FUN_004202cc
// callees: FUN_0049eb44

void FUN_0041ff98(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0049eb44(DAT_004b7a14,0xb,1,0x18,0,0);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004b7a14,0xb,1,0x27,0,0);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}

