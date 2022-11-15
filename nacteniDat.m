clear all

data = fopen('data.txt');

geom = zeros(1,2);
bnd = zeros(1,3);

line = fgetl(data);
k = 1;
pom = "";
lastSpc = false;
while ischar(line)
    j = 1;
    for i = 1:(strlength(line)+1)
        if i == (strlength(line)+1)
            if j == 4
                bnd(k,2) = str2double(pom);
                pom = "";
            elseif j == 5
                bnd(k,3) = str2double(pom);
                pom = "";
            end
        else
            if line(i) == " " && lastSpc == false
                if j < 3
                    geom(k, j) = str2double(pom);
                    pom = "";
                elseif j == 3
                    cislo = str2double(pom);
                    if cislo == 1 || cislo == 2 || cislo == 3
                        bnd(k,1) = cislo;
                    end
                    pom = "";
                elseif j == 4
                    bnd(k,2) = str2double(pom);
                    pom = "";
                end
                lastSpc = true;
                j = j + 1;
            elseif line(i) ~= " "
                pom = pom + line(i);
                lastSpc = false;
            end
            if pom == "#"
                break;
            end
        end
    end
    lastSpc = false;
    if pom ~= "#" && j >= 3
        k = k + 1;
    end
    pom = "";
    line = fgetl(data);
end


% kontrola nactenych dat

if(geom(1,:) ~= geom(length(geom(:,1)),:))
    disp("neuzavrena geometrie");
end

for i = 2:length(geom(:,1))
    if(geom(i-1,1) ~= geom(i,1) && geom(i-1,2) ~= geom(i,2))
        disp("nepravouhla geometrie");
    end
end


% priprava site------------------------------

dx = 1;
dy = dx;
xMax = max(geom(:,1));
yMax = max(geom(:,2));


UZLY = zeros(xMax/dx + 1, yMax/dy + 1);
for j = 1:length(UZLY(1,:))
	for i = 1:length(UZLY(:,1))
        count = 0;
        count2 = 0;
        x1 = (i-1)*dx;
        y1 = (j-1)*dy;
        x2 = xMax*2;
        y2 = y1;
        x22 = x1;
        y22 = yMax*2;
        for k = 2:length(geom(:,1))
            x3 = geom(k-1,1);
            y3 = geom(k-1,2);
            x4 = geom(k,1);
            y4 = geom(k,2);
            t = (((x1-x3)*(y3-y4))-(y1-y3)*(x3-x4))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
            u = (((x1-x3)*(y1-y2))-(y1-y3)*(x1-x2))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
            if 0 <= t && t <= 1 && 0 <= u && u <= 1
                count = count + 1;
            end
            t = (((x1-x3)*(y3-y4))-(y1-y3)*(x3-x4))/(((x1-x22)*(y3-y4))-((y1-y22)*(x3-x4)));
            u = (((x1-x3)*(y1-y22))-(y1-y3)*(x1-x22))/(((x1-x22)*(y3-y4))-((y1-y22)*(x3-x4)));
            if 0 <= t && t <= 1 && 0 <= u && u <= 1
                count2 = count2 + 1;
            end
            if (x3 <= x1 && x4 >= x1 && y3 == y4 && y1 == y3) || (x4 <= x1 && x3 >= x1 && y3 == y4 && y1 == y3) || (y3 <= y1 && y4 >= y1 && x3 == x4 && x1 == x3) || (y4 <= y1 && y3 >= y1 && x3 == x4 && x1 == x3)
                UZLY(i,j) = 2;
                count = 0;
                count2 = 0;
                break;
            end
       end
       if rem(count, 2) || rem(count2, 2)
            UZLY(i,j) = 1;
       end
	end
end




% UZLY = zeros(xMax/dx + 1, yMax/dy + 1);
% for j = 1:length(UZLY(1,:))
% 	for i = 1:length(UZLY(:,1))
%         count = 0;
%         x1 = (i-1)*dx;
%         y1 = (j-1)*dy;
%         x2 = xMax*2;
%         y2 = y1;
%         for k = 2:length(geom(:,1))
%             x3 = geom(k-1,1);
%             y3 = geom(k-1,2);
%             x4 = geom(k,1);
%             y4 = geom(k,2);
%             t = (((x1-x3)*(y3-y4))-(y1-y3)*(x3-x4))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
%             u = (((x1-x3)*(y1-y2))-(y1-y3)*(x1-x2))/(((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4)));
%             if 0 <= t && t <= 1 && 0 <= u && u <= 1 && y1 ~= y3 && y1 ~= y4
%                 count = count + 1;
%             end
%             if (((x1-x2)*(y3-y4))-((y1-y2)*(x3-x4))) == 0 && y1 == y3 && y1 == y4 && x1 <= x3 && x1 <= x4
%                 count = 1 + 1;
%             end
%             if (x3 <= x1 && x4 >= x1 && y3 == y4 && y1 == y3) || (x4 <= x1 && x3 >= x1 && y3 == y4 && y1 == y3) || (y3 <= y1 && y4 >= y1 && x3 == x4 && x1 == x3) || (y4 <= y1 && y3 >= y1 && x3 == x4 && x1 == x3)
%                 UZLY(i,j) = 2;
%                 count = 0;
%                 break;
%             end
%        end
%        if rem(count, 2)
%             UZLY(i,j) = 1;
%        end
% 	end
% end

% % odstraneni(pridani) vadnych uzlu-----------------------------------
% for j = 2:(length(UZLY(1,:)) - 1)
% 	for i = 2:(length(UZLY(:,1)) - 1)
%         if UZLY(i-1,j) == 1 && UZLY(i+1,j) == 1
%             UZLY(i,j) = 1;
%         end
%         if UZLY(i,j-1) == 1 && UZLY(i,j+1) == 1
%             UZLY(i,j) = 1;
%         end
% 	end
% end


% % vypocet-------------------------------------------------------------------------------------------------------------------------
a = 0.133;
dt = 0.025;
tMax = 30;

% 
% % pocatecni podminka---------------------------------------------------------------------
% % x0 = 20 + zeros((xMax/h)+1, (yMax/h)+1);
% x0 = zeros((xMax/h)+1, (yMax/h)+1);
% amp = 200;
% sigma = 1;
% xx = 5;
% yy = 5;
% 
% for n = 1:((yMax/h)+1)
% 	for m = 1:((xMax/h)+1)
%         x = (m-1)*h;
%         y = (n-1)*h;
%         x0(m,n) = amp*exp(-(((x-xx)^2)/(2*sigma^2)+((y-yy)^2)/(2*sigma^2))) + 20;
%     end
% end



% T = zeros((xMax/dx)+1, (yMax/dy)+1, tMax/dt);
% 
% for j = 1:(yMax/dy)+1
%     for i = 1:(xMax/dx)+1
%         if UZLY(i,j) == 1
%             T(i,j,1) = 20;
%         elseif UZLY(i,j) == 2
%             T(i,j,:) = 30;
%         else
%             T(i,j,:) = nan;
%         end
%     end
% end
    



% 
% if (a*dt)/(min(dx^2,dy^2)) < 0.5
%    disp("Stabilni"); 
% end
% 
% 
% 
% for k = 1:((tMax/dt)-1)
%     for n = 2:(yMax/dy)
%         for m = 2:(xMax/dx)
%             if UZLY(m,n) == 1
%                 T(m,n,k+1) = ((dt*a)/(dx*dx))*(T(m+1,n,k) + T(m-1,n,k) + T(m,n-1,k) + T(m,n+1,k) - 4*T(m,n,k)) + T(m,n,k);
%             end
%         end
%     end
% end




% % vykresleni hranice------------------------------------------------------------------------------------------------------------------------------------------------
% figure
% hold on
% for i = 2:length(geom(:,1))
%     plot([geom(i-1,1), geom(i,1)], [geom(i-1,2), geom(i,2)], "k");
% end
% 
% 

% vykresleni site--------------------------------------------
figure
hold on
for j = 1:length(UZLY(1,:))
    for i = 1:length(UZLY(:,1))
        if UZLY(i, j) == 1
            plot((i-1)*dx, (j-1)*dy, "k.");
        elseif UZLY(i, j) == 2
            plot((i-1)*dx, (j-1)*dy, "r.");
        end
    end
end

% obj = VideoWriter("animation.avi");
% obj.Quality = 100;
% obj.FrameRate = 25;
% open(obj);
% 
% for t = 1:((tMax/dt)/10)
%     surf(T(:,:,t*10));
%     caxis([20 30]);
%     zlim([20 30]);
% %     view(2);
%     hold off
% %     f = getframe(gcf);
% %     writeVideo(obj,f);
%     pause(0.1)
% end
% % obj.close();
% 



