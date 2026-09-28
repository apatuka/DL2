// FUN_004893dd @ 004893dd size=41 sig=undefined FUN_004893dd() cc=unknown
// callers: FUN_00495aa4,FUN_004934e0,FUN_00493522
// callees: FUN_0048f758,FUN_004a6964,FUN_00489320

void FUN_004893dd(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  
  uVar3 = 0x2e;
  uVar1 = FUN_00489320(param_1);
  pcVar2 = (char *)FUN_0048f758(uVar1,uVar3);
  if (*pcVar2 != '\0') {
    pcVar2 = pcVar2 + 1;
  }
  FUN_004a6964(param_2,pcVar2);
  return;
}

