/*--- Projektil ---*/

#strict

//local Airbuffer; // Luftwiderstand und so

//constAirbufferMax: return(1);

public Hit:
  Explode(18);
  return(1);

AdjustRotation:
/*  var FlightR = MakeThisAngleUseful(Angle(0,0,GetXDir(),GetYDir()),-180,180);
  var FlightSpeed = Sqrt( Pow(GetXDir(),2) , Pow(GetYDir(),2) );

  var CurrentR = MakeThisAngleUseful(GetR(),FlightR - 180, FlightR + 180 );

  if(!( GetXDir() || GetYDir() )) return(1);

  if( CurrentR > FlightR )
    DoRDir( -Max(1,FlightSpeed) );
  if( CurrentR < FlightR )
    DoRDir(  Max(1,FlightSpeed) );


  if(Airbuffer++ > constAirbufferMax() )
    {
      Airbuffer = 0;
      if(CurrentR > FlightR)
        DoR(-1);
      if(CurrentR < FlightR)
        DoR(1);
    };
  
*/
  SetR(Angle(0,0,GetXDir(),GetYDir()));



  return(1);

Pow:
  if(LessThan( Par(1),0 )) IncVar(2);
  IncVar();
  while(LessThan( Var(1),Abs(Par(1)) ))
    And(
      SetVar(0,Mul( Var(),Par() )),
      IncVar(1)
    );
  if(Var(2)) return(Div( 1,Var() ));
  return(Var());

DoR:
  return(SetR(GetR(Par(1)) + Par(),Par(1)));

DoRDir:
  return(SetRDir(GetRDir(Par(1)) + Par(),Par(1)));

/*MakeThisAngleUseful: // Winkel, -, +
  var Winkel = Par();
  while(Winkel > Par(2))
    Winkel = Winkel - 360;

  while(Winkel < Par(1))
    Winkel = Winkel + 360;

  return(Winkel);
*/
/* Kann chemisch werden */
public IsChemicalProduct: return(1);
