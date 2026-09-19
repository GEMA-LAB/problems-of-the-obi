{ Solucao para o problema "Overflow" da OBI 2009
   por: Igor Ribeiro de Assis }

program overflow;

var
   N, P, Q, total : longint;
   o		  : char;

begin 

   readln(N);
   readln(P, o, Q);

   if o = '+' then
      total := P + Q
   else
      total := P * Q;

   if total > N then
      writeln('OVERFLOW')
   else
      writeln('OK')

end.
