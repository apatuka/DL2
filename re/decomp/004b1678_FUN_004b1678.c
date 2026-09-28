// FUN_004b1678 @ 004b1678 size=93 sig=undefined FUN_004b1678() cc=unknown
// callers: FUN_004b16d8
// callees: FUN_004b3d84,FUN_004b3d58,sprintf
// strings: \"%02d/%02d/%04d %2d:%02d:%02d.%02d \"

undefined * FUN_004b1678(void)

{
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined1 local_9;
  undefined4 local_8;
  char local_4;
  char local_3;
  
  FUN_004b3d58(&local_8);
  FUN_004b3d84(&local_c);
  sprintf(&DAT_0069f784,s__02d__02d__04d__2d__02d__02d__02_0052127c,(int)local_3,(int)local_4,
          local_8,local_b,local_c,local_9,local_a);
  return &DAT_0069f784;
}

