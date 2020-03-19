#strict

Advance:
  if (!Random(30)) Branch();

  Var(0)=GetVertexNum()-1;

  if ( !AddVertex( GetVertex(Var(0),0)+Random(21)-10, GetVertex(Var(0),1)+Random(8)-12) ) return(Sequence());

  if (!InGround()) SetAction("Discharge");

  Var(1)=(Var(0)=GetVertexNum()-1)-1;

  DrawVolcanoBranch( Local(1),  GetVertex(Var(1),0), GetVertex(Var(1),1), GetVertex(Var(0),0), GetVertex(Var(0),1), Local(0) );
		
  if (!InBounds()) return(Remove());

  DecreaseSize();

  return(1);


CastLava:
  Var(0)=GetVertexNum()-1;
  CastPXS("Lava",Min(Local(0),5),20,GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY());
  if (Local(0)>10) if (!Random(5)) CastObjects(LAVA,1,45,GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY());
  if (!Random(10)) Sound("Discharge");
  return(1);

Activate:
  AddVertex(Par(0),Par(1));
  Local(0)=Par(2);
  Local(1)=Par(3);
  if (!InGround()) return(Remove());
  SetAction("Advance");
  if (!Random(5)) Sound("Lava*");
  return(1);


Remove:
  RemoveObject();
  return(1);


InGround:
  Var(0)=GetVertexNum()-1;
  if ( GBackSolid( GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY()) ) return(1);
  if (GetMaterial( GetVertex(Var(0),0)-GetX(), GetVertex(Var(0),1)-GetY()) == Local(1)) return(1);
  return(0);

InBounds:
  Var(0)=GetVertexNum()-1;
  if (!Inside( GetVertex(Var(0),0), 0, LandscapeWidth() )) return();
  if (!Inside( GetVertex(Var(0),1), 0, LandscapeHeight() )) return();
  return(1);

Branch:
  Var(0)=GetVertexNum()-1;
  Var(1)=CreateObject(FXV1,0,0,-1);
  Var(2)=Random(Local(0));
  ObjectCall(Var(1),"Activate",GetVertex(Var(0),0),GetVertex(Var(0),1),Var(2),Local(1));
  Local(0)-=Var(2);
  return(1);

Sequence:
  Var(0)=GetVertexNum()-1;
  Var(1)=CreateObject(FXV1,0,0,-1);
  ObjectCall(Var(1),"Activate",GetVertex(Var(0),0),GetVertex(Var(0),1),Local(0),Local(1));
  Remove();
  return(1);

DecreaseSize:
  if (Random(5)) return(1);
  if (--Local()<1) Remove();
  return(1);
