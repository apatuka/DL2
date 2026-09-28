// FUN_00478fec @ 00478fec size=99 sig=undefined FUN_00478fec() cc=unknown
// callers: FUN_00479a88,FUN_0047c4f8,FUN_00479ee0
// callees: 

void FUN_00478fec(byte *param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  byte *pbVar5;
  
  uVar4 = 0;
  if (param_3 != 0) {
    do {
      bVar2 = *param_1;
      pbVar5 = param_1 + 1;
      if ((bVar2 & 0x80) == 0) {
        bVar2 = bVar2 + 1;
        bVar3 = bVar2;
        while (bVar3 != 0) {
          bVar1 = *pbVar5;
          pbVar5 = pbVar5 + 1;
          *param_2 = bVar1;
          param_2 = param_2 + 1;
          bVar3 = bVar3 - 1;
        }
      }
      else {
        bVar2 = 1 - bVar2;
        bVar3 = *pbVar5;
        pbVar5 = param_1 + 2;
        bVar1 = bVar2;
        while (bVar1 != 0) {
          *param_2 = bVar3;
          param_2 = param_2 + 1;
          bVar1 = bVar1 - 1;
        }
      }
      uVar4 = uVar4 + bVar2;
      param_1 = pbVar5;
    } while (uVar4 < param_3);
  }
  return;
}

