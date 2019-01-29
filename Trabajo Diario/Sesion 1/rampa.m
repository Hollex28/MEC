function [valor,tiempo] = rampa(vi,vf,t1,t2,incr)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
valor(1) = vi;
    for i=2:t1+1
        v = valor(i-1)+incr;
        valor(i) = v;
    end
    valor(t1)=vf;
    for i = t1:t2
        v = valor(t1);
        valor(i) = v;
    end
    for i=1:t2
        tiempo(i) = i-1;
    end
    
end

