program marciano;

var
   L, A, P, R: longint;
begin
   readln(L, A, P, R);
   if L*L + A*A + P*P > 4*R*R then
      writeln('N')
   else
      writeln('S')
end.
