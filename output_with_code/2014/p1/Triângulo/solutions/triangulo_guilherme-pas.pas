(* Guilherme A. Pinto - OBI 2014 - Triangulo *)
program triang(input,output);
var
   a,b,c,d:integer;

function triangulo(var p,q,r:integer):boolean;
begin
   triangulo := false;
   if ( (p < q+r) and 
        (q < p+r) and 
        (r < p+q) ) then triangulo := true;
end;

begin
  readln(a,b,c,d);
  if ( triangulo( a, b, c ) or
       triangulo( a, b, d ) or
       triangulo( a, c, d ) or
       triangulo( b, c, d ) ) then writeln('S')
  else writeln('N');
end.
