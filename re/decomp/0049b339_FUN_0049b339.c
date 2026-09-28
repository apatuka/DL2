// FUN_0049b339 @ 0049b339 size=144 sig=undefined FUN_0049b339() cc=unknown
// callers: FUN_0049e638
// callees: 

uint FUN_0049b339(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((*(byte *)(param_1 + 6) & 0xf) == 0) {
    param_1 = param_1 + param_3 * 4;
    if (param_2 == 1) {
      uVar1 = (*(byte *)(param_1 + 8) & 0xf8) << 7 | (*(byte *)(param_1 + 9) & 0xf8) << 2 |
              (int)(uint)*(byte *)(param_1 + 10) >> 3;
    }
    else if (param_2 == 2) {
      uVar1 = (*(byte *)(param_1 + 8) & 0xf8) << 8 | (*(byte *)(param_1 + 9) & 0xfc) << 3 |
              (int)(uint)*(byte *)(param_1 + 10) >> 3;
    }
  }
  return uVar1;
}

