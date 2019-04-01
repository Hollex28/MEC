clear

tt=0:0.02:17.98

% e=0.020
% b=0.056
% r=0.028
% kmp=9;
% krp=4;
% krv=0.5;

incre=0.0041;

k=1;

for k=1:1000

    if ((k>0) & (k<226))
        xref(k)=incre*k;
        yref(k)=0;
    end

    if ((k>225) & (k<451))
        xref(k)=incre*225;
        yref(k)=(k-225)*incre;
    end

    if ((k>450) & (k<676))
        xref(k)=incre*225-incre*(k-450);
        yref(k)=incre*225;
    end;
 

    if ((k>675) & (k<901))
        xref(k)=0;
        yref(k)=incre*225-incre*(k-675);
    end;
    
end;

xxref=[tt' xref']
yyref=[tt' yref']

