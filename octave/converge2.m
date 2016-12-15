start = 2;
finish = 1000;
j=1;
for i =start:finish
	x(j)=std(mean(randn(1000,i)));
	j=j+1;
end
disp('Plotting...');
%plot(j,x);