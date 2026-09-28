// FUN_004a3439 @ 004a3439 size=250 sig=undefined FUN_004a3439() cc=unknown
// callers: FUN_004a3533
// callees: FUN_0048f774

void FUN_004a3439(undefined4 param_1,int param_2)

{
  int iVar1;
  
  FUN_0048f774(param_2,0x130,0);
  *(undefined4 *)(param_2 + 0x104) = 1;
  *(undefined4 *)(param_2 + 0x9c) = 0xc0000000;
  *(undefined4 *)(param_2 + 0xa8) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xa0) = 0xc0000000;
  *(undefined4 *)(param_2 + 0xac) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xa4) = 0xc03f3f3f;
  *(undefined4 *)(param_2 + 0xb0) = 0xc07f7f7f;
  *(undefined4 *)(param_2 + 0xb4) = 0xc0000000;
  *(undefined4 *)(param_2 + 0xc0) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xb8) = 0xc0000000;
  *(undefined4 *)(param_2 + 0xc4) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xbc) = 0xc03f3f3f;
  *(undefined4 *)(param_2 + 200) = 0xc07f7f7f;
  *(undefined4 *)(param_2 + 0xcc) = 0xc0000000;
  *(undefined4 *)(param_2 + 0xd8) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xd0) = 0xc000ff00;
  *(undefined4 *)(param_2 + 0xdc) = 0xc0ffffff;
  *(undefined4 *)(param_2 + 0xd4) = 0xc03f3f3f;
  *(undefined4 *)(param_2 + 0xe0) = 0xc07f7f7f;
  *(undefined4 *)(param_2 + 0x108) = 9;
  iVar1 = 0;
  do {
    *(undefined4 *)(param_2 + 0x10c + iVar1 * 4) = 0xffffffff;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  *(undefined4 *)(param_2 + 8) = param_1;
  return;
}

