function [a1,z1,a2,z2]=forwardprop(W1,W2,Z) 
a1=W1*Z;
z1=zeros(size(a1,1)+1, 1);
z1(1,1)=1;
for i=1:size(a1,1) 
    z1(i+1,1)=1/(1+exp(-1*a1(i,1)));
end
a2=W2*z1;
z2=zeros(size(a2,2),1);
z2(1,1)=1/(1+exp(a2(1,1)));