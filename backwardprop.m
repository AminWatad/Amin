function [d1, d2]=backwardprop(A1,W2,Z2,Y) 
d2=Z2(1,1)-Y;
d1=zeros(size(A1,1),1);
X=W2'*d2;
for i=1:size(d1,1)
    d1(i,1)= ((1/(1+exp(-1*A1(i,1))))*(1-(1/(1+exp(-1*A1(i,1))))))*X(i+1,1);
end