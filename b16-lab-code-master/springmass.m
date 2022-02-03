clear
clc
%%%%
spring=readmatrix('springmass.txt');
plot(spring(:,1),spring(:,2),spring(:,3),spring(:,4))
axis square
grid on
xlim([-1,1])
ylim([-1,1])