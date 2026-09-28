// FUN_0040b8f4 @ 0040b8f4 size=115 sig=undefined FUN_0040b8f4() cc=unknown
// callers: FUN_00401ac0
// callees: FUN_004726cc

undefined4 FUN_0040b8f4(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = FUN_004726cc(*(undefined4 *)(param_1 + 0x3c),param_2,(int)*(char *)(param_1 + 8));
  if (iVar2 == 2) {
    bVar1 = *(byte *)(*(int *)(param_1 + 0x3c) + 0x22);
    if (((((1 << (bVar1 & 0x1f) &
           *(uint *)((int)&DAT_0055a82c + (char)*(byte *)(param_2 + 0x22) * 0x1a2)) != 0) ||
         (bVar1 == *(byte *)(param_2 + 0x22))) &&
        ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x01')) &&
       (*(char *)(param_2 + 0x21) != '\0')) {
      return 1;
    }
  }
  return 0;
}

