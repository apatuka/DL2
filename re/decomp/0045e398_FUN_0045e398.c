// FUN_0045e398 @ 0045e398 size=345 sig=undefined FUN_0045e398() cc=unknown
// callers: FUN_0044a358,FUN_0044a5e8,FUN_0044a48c,FUN_0047361c
// callees: FUN_0045e0b4,FUN_00418e00,FUN_0045e13c,FUN_00449f5c,FUN_00449dec

int FUN_0045e398(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((DAT_004d59b4 == 0) || ((DAT_004d59b4 == 0x22 && (cVar1 = FUN_00418e00(), cVar1 != '\0')))) {
    if (DAT_004d5ad0 == 0) {
      if (param_1 == 0) {
        FUN_0045e0b4(DAT_004c5b54 - param_2,DAT_004c5b58);
        iVar2 = DAT_004c5b54;
      }
      else if (param_1 == 1) {
        FUN_0045e0b4(param_2 + DAT_004c5b54,DAT_004c5b58);
        iVar2 = DAT_004c5b54;
      }
      else if (param_1 == 2) {
        FUN_0045e0b4(DAT_004c5b54,DAT_004c5b58 - param_2);
        iVar2 = DAT_004c5b58;
      }
      else if (param_1 == 3) {
        FUN_0045e0b4(DAT_004c5b54,param_2 + DAT_004c5b58);
        iVar2 = DAT_004c5b58;
      }
    }
    else if (param_1 == 0) {
      FUN_0045e13c(DAT_004c4a58 - param_2,DAT_004c4a5c);
      iVar2 = DAT_004c4a58;
    }
    else if (param_1 == 1) {
      FUN_0045e13c(param_2 + DAT_004c4a58,DAT_004c4a5c);
      iVar2 = DAT_004c4a58;
    }
    else if (param_1 == 2) {
      FUN_0045e13c(DAT_004c4a58,DAT_004c4a5c - param_2);
      iVar2 = DAT_004c4a5c;
    }
    else if (param_1 == 3) {
      FUN_0045e13c(DAT_004c4a58,param_2 + DAT_004c4a5c);
      iVar2 = DAT_004c4a5c;
    }
    FUN_00449dec();
    FUN_00449f5c();
  }
  return iVar2;
}

