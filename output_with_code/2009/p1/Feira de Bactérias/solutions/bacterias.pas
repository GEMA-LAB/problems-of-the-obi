{ Solucao para o problema "Feira de Bactérias" da OBI 2009
  por: Igor Ribeiro de Assis }

program bacterias;

var
   N, res, i  : longint;
   bact, D, C : real;

begin 
   bact := 0.0;
   
   readln(N);
   for i := 1 to N do begin
      readln(D, C);
      { se A > B então log(A) > log(B) }
      if bact < C*ln(D) then begin
	 { log(C^D) = C*log(D) }
	 bact := C*ln(D);
	 res := i;
      end;
   end;

   writeln(res);
end.
   