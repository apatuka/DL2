// FUN_00482fc8 @ 00482fc8 size=65 sig=undefined FUN_00482fc8() cc=unknown
// callers: FUN_00483224,LoadPhaseSpriteFile,FUN_00483538
// callees: 

void FUN_00482fc8(uint param_1)

{
  undefined *puVar1;
  
  *(uint *)(&DAT_00657e60 + (param_1 & 0xfffffffc)) =
       *(uint *)(&DAT_00657e60 + (param_1 & 0xfffffffc)) & ~(1 << ((byte)param_1 & 3));
  for (puVar1 = (&PTR_DAT_004d02f4)[param_1 * 3]; *(short *)(puVar1 + 4) != 0;
      puVar1 = puVar1 + 0x10) {
    *(undefined4 *)(puVar1 + 8) = 0;
  }
  return;
}

