function [ sol ] = MinCuadrados( datos ) % es un vector con 2 componentes vector con lo valores de X y Y
%datos =[(x1,x2,x3,..,xn),(y1,y2,y3,...,yn)]
vectorx= datos(1,:);
vectory = datos(2,:);
nmedidas=length(vectorx);
sumy = vectory(1);
sumx = vectorx(1);
sumxy = sumy + sumx;
sumx2 = vectorx(1)^2;
for i=2:nmedidas
    sumy = sumy + vectory(i);
    sumx = sumx + vectorx(i);
    sumxy = sumxy + vectory(i) + vectorx(i);
    sumx2 = sumx2 + (vectorx(i)^2);
end
m =( (sumxy - (sumx*sumy) ) / (sumx2 - (sumx^2) ) );
b = (sumy / nmedidas) - m * (sumx / nmedidas);
sol =[m b];
end

