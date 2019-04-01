% Calcula el �ndice del punto del camino que est� m�s pr�ximo a encontrarse
% a una distancia LA del veh�culo

% se considera que el camino es "infinito": detr�s del �ltimo punto del camino, vuelve a estar el 1� punto 

function [sal]= calcula_indice(u)

% no se analiza todo el camino, sino el ratio que se indica
windowRatio=4;

% n� de puntos del camino
long = (length(u)-4)/2; 

% en "u" est�n todas la variables una detr�s de otra. Hay que sacarlas del
% par�metro de entrada u
x_camino = u(1:long);   % coordenadas X del camino 
y_camino = u(long+1:2*long); % coordenadas Y del camino
x_vehiculo = u(2*long+1); % posisicion X del robot
y_vehiculo = u(2*long+2); % posici�n Y del robot
dista_fija = u(2*long+3); % distancia fija de separaci�n que se desea entre robot y (xob, yob)
k = u(2*long+4);  % indice del punto m�s cercano del camino al robot iteraci�n anterior

% calculo de la distancia entre el robot y todos los puntos del camino 
dist=sqrt( (x_camino-x_vehiculo).^2+(y_camino-y_vehiculo).^2 );

% valor (abs) entre la distancia entre el robot y el camino y la distancia fija 
dif = abs(dist-dista_fija);

% n� puntos del camino que se van a analizar: depende el ratio que se desee
% (la 1/4 parte), p.e.
amirar=floor(length(x_camino)/windowRatio);

% n� de puntos que quedan por analizar del camino
quedan=long-k+1;

if quedan < amirar
    % si "quedan" es menor que el n� de puntos a analizar, estamos al final del
    % del vector del camino. Para que la trayectoria sea "infinita" hay que
    % concatenar los primero puntos del camino
    dif_delante=[dif(k:long);dif(1:amirar-quedan)];
else
    % como quedan m�s puntos en el camino que los que hay que mirar,
    % se cogen directamente esos puntos
    dif_delante=dif(k:k+amirar-1);
end

% se obtiene el �ndice el punto del camino cuya distancia es la menor
[z,indice] = min(dif_delante);
k = indice + k -1;

% el camino es "infinito": detr�s del �ltimo punto vuelve a estar el 1�
% hay que considerar el m�dulo del �ndice 
k=mod(k,long);
if k==0
    k=1; % en Matlab los vectores empiezan en 1, no en 0 como en C
end

% (x_ob, y_ob): punto objetivo del robot
x_ob=x_camino(k);
y_ob=y_camino(k);

% la funci�n devuelve el punto objetivo y el valor del �ndice del vector
% del camino
sal=[x_ob y_ob k];