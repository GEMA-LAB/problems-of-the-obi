(* Guilherme A. Pinto - OBI 2014 - Setas *)

program setas(input,output);
const
   MAXN	= 500;

var
   s	 : array [1..(MAXN+2),1..(MAXN+2)] of char;
   ans	 : longint;
   i,j,N : longint;

function solve(i, j :integer ): char;
var
   a,b : integer;
begin

  if ( (s[i,j] = 's') or (s[i,j] = '*') ) then
     solve := s[i,j]
  else begin
     a := i; b := j;
     if ( s[i,j] = 'A' ) then a := a-1;
     if ( s[i,j] = 'V' ) then a := a+1;
     if ( s[i,j] = '<' ) then b := b-1;
     if ( s[i,j] = '>' ) then b := b+1;
     s[i,j] := 's';
     s[i,j] := solve( a, b );
     if ( s[i,j] = '*' ) then ans := ans + 1;
     solve := s[i,j];
  end;
end;

begin
   readln(N);
   for j := 1 to N+2 do s[1,j] := '*';
   for i := 2 to N+1 do
      begin
	 s[i,1] := '*';
	 for j := 2 to N do read(s[i,j]);
	 readln(s[i,N+1]);
	 s[i,N+2] := '*';
      end;
   for j := 1 to N+2 do s[N+2,j] := '*';

   ans := 0;
   for i := 2 to N+1 do
      for j := 2 to N+1 do
	 if ( not (s[i,j] = '*') ) then
	    solve( i, j );

   writeln((N*N)-ans);
end.
