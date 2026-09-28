// FUN_0047f23c @ 0047f23c size=514 sig=undefined FUN_0047f23c() cc=unknown
// callers: FUN_004810cc
// callees: FUN_00464444,FUN_0047f1d8,FUN_0047edbc

void FUN_0047f23c(int param_1,undefined4 param_2)

{
  uint uVar1;
  ushort uVar2;
  uint *puVar3;
  int iVar4;
  bool bVar5;
  int local_c;
  int local_8;
  
  iVar4 = 0;
  puVar3 = &DAT_004dcd00;
  do {
    uVar1 = *puVar3;
    FUN_0047edbc((int)uVar1 % 6,(int)uVar1 / 6,&local_8,&local_c);
    uVar2 = *(ushort *)(param_1 + 0x142 + uVar1 * 0x34) & 0xff;
    if (uVar2 == 5) {
      if ((int)uVar1 < 0x13) {
        if ((uVar1 == 0x12) || (((uVar1 == 0 || (uVar1 == 6)) || (uVar1 == 0xc))))
        goto LAB_0047f2cb;
LAB_0047f2d2:
        bVar5 = *(short *)(param_1 + 0x10e + uVar1 * 0x34) != 5;
      }
      else {
        if ((uVar1 != 0x18) && (uVar1 != 0x1e)) goto LAB_0047f2d2;
LAB_0047f2cb:
        bVar5 = true;
      }
      if (bVar5) {
        FUN_00464444(local_8,local_c + 0x19,local_8 + 0x32,local_c,param_2);
      }
      if (uVar1 - 0x1e < 6) {
        bVar5 = true;
      }
      else {
        bVar5 = *(short *)(param_1 + 0x27a + uVar1 * 0x34) != 5;
      }
      if (bVar5) {
        FUN_00464444(local_8,local_c + 0x19,local_8 + 0x32,local_c + 0x32,param_2);
      }
      if (uVar1 < 6) {
        bVar5 = true;
      }
      else {
        bVar5 = *(short *)(param_1 + 10 + uVar1 * 0x34) != 5;
      }
      if (bVar5) {
        FUN_00464444(local_8 + 0x32,local_c,local_8 + 100,local_c + 0x19,param_2);
      }
      if ((int)uVar1 < 0x18) {
        if (((uVar1 == 0x17) || ((uVar1 == 5 || (uVar1 == 0xb)))) || (uVar1 == 0x11))
        goto LAB_0047f3cf;
LAB_0047f3d6:
        bVar5 = *(short *)(param_1 + 0x176 + uVar1 * 0x34) != 5;
      }
      else {
        if ((uVar1 != 0x1d) && (uVar1 != 0x23)) goto LAB_0047f3d6;
LAB_0047f3cf:
        bVar5 = true;
      }
      if (bVar5) {
        FUN_00464444(local_8 + 0x32,local_c + 0x32,local_8 + 100,local_c + 0x19,param_2);
      }
    }
    else if ((uVar2 != 6) && (uVar2 != 0xff)) {
      FUN_0047f1d8(local_8,local_c,0xb);
    }
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
    if (0x23 < iVar4) {
      return;
    }
  } while( true );
}

