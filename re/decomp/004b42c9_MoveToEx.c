// MoveToEx @ 004b42c9 size=6 sig=BOOL MoveToEx(HDC hdc, int x, int y, LPPOINT lppt) cc=__stdcall
// callers: FUN_00464f80,FUN_00457bec
// callees: 

BOOL MoveToEx(HDC hdc,int x,int y,LPPOINT lppt)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MoveToEx(hdc,x,y,lppt);
  return BVar1;
}

