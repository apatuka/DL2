// FUN_0044d7b4 @ 0044d7b4 size=217 sig=undefined FUN_0044d7b4() cc=unknown
// callers: FUN_0044db50,FUN_0044f3f0,FUN_0044dcf4
// callees: 

void FUN_0044d7b4(int param_1,undefined4 param_2,int param_3,int param_4)

{
  byte *pbVar1;
  ushort *puVar2;
  ushort uVar3;
  
  *(undefined4 *)(param_1 + 0x154 + param_3 * 0x34) = param_2;
  if (param_4 == 5) {
    puVar2 = (ushort *)(param_1 + -0x336 + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x3100;
    puVar2 = (ushort *)(param_1 + -0x12e + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x1100;
    puVar2 = (ushort *)(param_1 + -0xc6 + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x5100;
    puVar2 = (ushort *)(param_1 + -0x5e + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x4100;
    puVar2 = (ushort *)(param_1 + 0x1aa + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x2100;
    puVar2 = (ushort *)(param_1 + -0x39e + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x6000;
  }
  else if (param_4 == 2) {
    puVar2 = (ushort *)(param_1 + 0x142 + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x1000;
    puVar2 = (ushort *)(param_1 + 0x176 + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x2000;
    puVar2 = (ushort *)(param_1 + 10 + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x3000;
    puVar2 = (ushort *)(param_1 + 0x3e + param_3 * 0x34);
    *puVar2 = *puVar2 | 0x4000;
    *(undefined1 *)(param_1 + 0x184 + param_3 * 0x34) = 0;
    pbVar1 = (byte *)(param_1 + 0x4c + param_3 * 0x34);
    *pbVar1 = *pbVar1 & 0xfb;
    pbVar1 = (byte *)(param_1 + 0x150 + param_3 * 0x34);
    *pbVar1 = *pbVar1 & 0xfd;
  }
  else {
    uVar3 = *(ushort *)(param_1 + 0x142 + param_3 * 0x34);
    if ((uVar3 & 0xf00) == 0x100) {
      *(ushort *)(param_1 + 0x142 + param_3 * 0x34) = uVar3 & 0xff | 0x3200;
    }
    else {
      puVar2 = (ushort *)(param_1 + 0x142 + param_3 * 0x34);
      *puVar2 = *puVar2 | 0x3000;
    }
  }
  return;
}

