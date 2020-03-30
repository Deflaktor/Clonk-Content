Initialize:
  Sound("LightWave");
  SetLocal(2,FindObject(KR3A,-5,-5,10,10));
  SetLocal(3,GetX(Local(2)));
  SetLocal(4,GetY(Local(2)));
  if(Equal(GetDir(Local(2)),DIR_Left())) Call("Liii");
  if(Equal(GetDir(Local(2)),DIR_Right())) Call("Reee");
  //Log("test: %d", Local(2));
  return(1);

Reee:
  SetAction("Los");
  SetPosition(Sum(Local(3),15),Sum(Local(4),-2),this());
  SetXDir(50);
  return(1);

Liii:
  SetAction("Los");
  SetPosition(Sum(Local(3),-15),Sum(Local(4),-2),this());
  SetXDir(-50);
  return(1);


Hit:
  Explode(15);
  //CastObjects(HF3A, 4, 20 );
  RemoveObject();
  return(1);

CheckforHit:
  if(GreaterThan(GetActTime(),400)) RemoveObject();
  if(SetLocal(1,FindObject(0,-10,-10,20,20,OCF_Living()))) 
   if(Not(Equal(Local(1),Local(2))))
    if(Not(SEqual(GetAction(Local(1)), "Dead")))
     Call("Hit");
  CastObjects(_TRS,1,10,0,4);
  return(1);

