function [W1,W2]=trainneuralnet(X,Y,nhid,lambda)
W1=randn(nhid,size(X,2));
W2=randn(1,nhid+1);
converged = 0;
iterations = 0;
while (converged ~= 1)
    SW1=0;
    SW2=0;
    iterations=iterations+1;
    lsum = 0;
    for i=1:size(X,1)
        [a1,z1,a2,z2] = forwardprop(W1,W2,X(i,:)');
        [d1,d2]=backwardprop(a1,W2,z2,Y(i,1));
        lsum=lsum-1*(Y(i,1)*log(z2(1,1))+(1-Y(i,1))*log(1-z2(1,1)));
        DW1=-0.1*d1*X(i,:);
        DW2=-0.1*d2*z1';
        SW1=SW1+DW1;
        SW2=SW2+DW2;
    end
    SUM = 0;
    for i=1:size(W1,1)
        for j=1:size(W1,2)
            SUM = SUM + W1(i,j)^2;
        end
    end
    for i=1:size(W2,2)
        SUM = SUM + W2(1,i)^2;
    end
    L=0;
    L=lsum/size(X,1) + lambda*SUM;
    SW1=SW1*L;
    SW2=SW2*L;
    ELMAX=0;
    for i=1:size(d1,1)
        if(d1(i,1) > ELMAX)
            ELMAX=d1(i,1);
        end
    end
    if (d2(1,1)>ELMAX)
        ELMAX=d2(1,1);
    end
    if (ELMAX < 0.0001)
        converged=1;
    end
    if(converged ~=1)
        W1=W1-0.1*SW1;
        W2=W2-0.1*SW2;
    end
    if(mod(iterations,1000) == 0)
      disp(ELMAX);
    end
end