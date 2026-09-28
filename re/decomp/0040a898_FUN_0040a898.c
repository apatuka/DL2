// FUN_0040a898 @ 0040a898 size=524 sig=undefined FUN_0040a898() cc=unknown
// callers: FUN_0040aaa4
// callees: FUN_0040be04,FUN_0040c68c,FUN_0040c74c

void FUN_0040a898(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  puVar4 = (undefined4 *)0x0;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    puVar3 = puVar4;
    if ((*(char *)((int)puVar2 + 0x7e) != '\0') && (*(short *)(puVar2 + 0x29b) < 3)) {
      if ((int)puVar2[param_1 + 0x25e] < 1) {
        if (((int)puVar2[param_1 + 0x25e] < 0) &&
           (puVar3 = puVar2, *(char *)((int)puVar2 + 0x21) == '\0')) {
          puVar3 = puVar4;
          local_8 = puVar2;
        }
      }
      else if (*(char *)(puVar2 + 8) == -1) {
        if ((*(char *)((int)puVar2 + 0x21) == '\0') ||
           (iVar1 = FUN_0040c68c(param_1,5,puVar2), iVar1 != 0)) {
          if ((*(char *)((int)puVar2 + 0x21) == '\0') &&
             (iVar1 = FUN_0040c68c(param_1,0xd,puVar2), iVar1 == 0)) {
            FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,0xd,100);
          }
        }
        else {
          FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,5,100);
        }
      }
      else if ((param_1 == *(char *)(puVar2 + 8)) && (*(short *)(puVar2 + 0xc) == 0)) {
        if ((*(char *)((int)puVar2 + 0x21) == '\0') ||
           (iVar1 = FUN_0040c68c(param_1,2,puVar2), iVar1 != 0)) {
          if ((*(char *)((int)puVar2 + 0x21) == '\0') &&
             (iVar1 = FUN_0040c74c(param_1,10), iVar1 == 0)) {
            FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,10,100);
          }
        }
        else {
          FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,2,100);
        }
      }
      else if ((1 << (*(byte *)(puVar2 + 8) & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) != 0)
      {
        if ((*(char *)((int)puVar2 + 0x21) == '\0') ||
           (iVar1 = FUN_0040c68c(param_1,3,puVar2), iVar1 != 0)) {
          if ((*(char *)((int)puVar2 + 0x21) == '\0') &&
             (iVar1 = FUN_0040c68c(param_1,0xb,puVar2), iVar1 == 0)) {
            FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,0xb,100);
          }
        }
        else {
          FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar2,3,100);
        }
      }
    }
    puVar4 = puVar3;
  }
  if ((puVar4 != (undefined4 *)0x0) && (iVar1 = FUN_0040c74c(param_1,8), iVar1 == 0)) {
    FUN_0040be04(param_1,0xffffffff,0xffffffff,puVar4,8,100);
  }
  if ((local_8 != (undefined4 *)0x0) && (iVar1 = FUN_0040c74c(param_1,0x10), iVar1 == 0)) {
    FUN_0040be04(param_1,0xffffffff,0xffffffff,local_8,0x10,100);
  }
  return;
}

