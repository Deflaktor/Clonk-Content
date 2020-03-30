// Author:major}

#strict

local ziel;

Activate:
  Sound("Thunder*");
SetPosition(GetX(Par()),GetY(Par()));
ziel=Par();
SetLocal(0,10); //bestimmt den Abstand der Meteore: Anzahl=Local(9)/Var()
SetLocal(12,1);      //bestimmt die Anzahl der Meteore pro Abstand
SetLocal(9,360);

//SetLocal(3,GetX(Par()));
//SetLocal(4,GetY(Par()));

SetLocal(6,2);  //Abweichung
SetLocal(7,2);  //der Meteore

while(Local(9)>180)
{

SetLocal(2,Local(2)+1);
if(Local(2)==Local(0))
  {
  SetLocal(10,Cos(Local(9),30)); //
  SetLocal(11,Sin(Local(9),30)); //jaja die wird man nie los...
  SetLocal(13,Local(12));

   CastParticles("wolke", 50,50,GetX(ziel)+Local(10)-GetX(),GetY(ziel)+Local(11)-GetY(), 8, 15, RGB(100), RGB(255));
   CreateParticle("MSpark",GetX(ziel)+Local(10)-GetX(),GetY(ziel)+Local(11)-GetY(), Local(10)*5,Local(11)*5, 500, RGBa(200,150,50,80));

  while(Local(13))
  {
    
     SetLocal(13,Local(13)-1);
     SetLocal(14,Var()=CreateObject(METO,Local(10)*2,Local(11)*2));
     // CastParticles("wolke", 50,50, GetX(Var())-GetX(),GetY(Var())-GetY(), 2, 15, RGB(100), RGB(255));
     //CreateParticle("wolke", GetX(Var())-GetX(),GetY(Var())-GetY(), 0,-10, 500, RGBa(200,RandomX(50,150),50,80));
     SetXDir(Local(10)*5,Local(14));
     SetYDir(Local(11)*5,Local(14));
  }
  
  SetLocal(2,0);
  }

SetLocal(9,Local(9)-1);

}

RemoveObject();

return(1);