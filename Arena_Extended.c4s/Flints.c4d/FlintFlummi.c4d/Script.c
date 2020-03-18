#strict
#include PRNT

//Local 0 = Y
//Local 1 = X
//Local 2 = Sprünge
//Local 3 = voreingestellte Sprünge


Initialize:
 SetAction("Fly");
 SetLocal(3,10);
 SetLocal(4,1);
return(1);

Damage:
  // Explode(50);
  return(1);

Activate:
 SetLocal(4,1);
 SetLocal(3,Sum(Local(3),1));
 if(Equal (Local(3), 11)) SetLocal(4,0);
 if(Equal (Local(3), 11)) SetLocal(3,0);
 if(Local(4))
 Message("%d",this(),Local(3));
 else
 Message("Keine Explosion",this());
return(1);

Hit:
 Sound("Boing");
 if(Equal(Local(4),1)) SetLocal(2,Sum(Local(2),1));                              // erhöhen
 if(Equal(Local(4),1)) Message("%d",this(),Sub(Local(3),Local(2)));
 if(Equal(Local(4),1)) if(Local(2)>=Local(3)) Explode(50);                // explodieren
 if(GBackSolid( 0,-1)) SetXDir(Mul (GetXDir(),-1) );       // oben
 if(GBackSolid(-1, 0)) SetXDir(Mul (GetXDir(),-1) );       // links
 if(GBackSolid( 1, 0)) SetXDir(Mul (GetXDir(),-1) );       // rechts
 if( GreaterThan( Div (Mul(Local(0),15),100), 0)) SetYDir(Sum (Mul (Local(0),-1) ,Div (Mul(Local(0),15),100) ) ,this()); // unten
 if(Equal(-15,GetYDir())) SetYDir(-14, this());
return(1);

Check:
 SetLocal(0,GetYDir());
 SetLocal(1,GetXDir());
return(1);