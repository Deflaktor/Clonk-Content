#strict

Check:
  /*if(GetOwner()==1) {
  if(Local(5) != Local(0))
    Log(Format("%d",Local(0)));
  Local(5) = Local(0);
  } */
  if(Local(0)>0) {

    SetLocal(1,Local(1)+1);

    if(Local(1)>10) {
      if(Local(0)==2)
        Sound("doublekill",1);
      if(Local(0)==3)
        Sound("multikill",1);
      if(Local(0)==4)
        Sound("ultrakill",1);
      if(Local(0)>=5&&Local(0)<=9)
        Sound("monsterkill",1);
      if(Local(0)>=10) {
	    SetAction("Timer");
        SetLocal(0,10);
        Sound("ludicrouskill",1);
	    SetWealth(GetOwner(),GetWealth(GetOwner())+310);
	    MusicLevel(10);
      }
      SetWealth(GetOwner(),GetWealth(GetOwner())+2**(Local(0)-3)*5);
      DoCrewExp(2**(Local(0)-3)*4,GetCrew(GetOwner()));
      DoCrewExp(Local(0)*10,GetCrew(GetOwner()));
      SetLocal(0);
      SetLocal(1);
    }
  }
  return(1);

End:
  MusicLevel(100-GameCall("MusicVolume"));
  SetAction("Idle");
  return(1);