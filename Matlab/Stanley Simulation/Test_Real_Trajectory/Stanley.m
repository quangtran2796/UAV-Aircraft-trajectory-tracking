%% Desired parameters
tra_x = [1190758.03 1190768.408 1190783.537 1190801.523 1190754.863 1190716.183 1190696.944 1190737.209];
tra_y = [11884721.84 11884710.52 11884701.22 11884678.87 11884656.58 11884632.74 11884653.73 11884706];
%tra_y = [14 17 18 21 19 17 15 12 10 7 6 4 3 0];
init_pos = [10.769447*110567 106.760922*111321];
init_angle = pi/2;
plot(tra_x, tra_y);
slope = [];   %Tao mang trong cho du lieu goc nghieng a     
d = [];    % Tao mang trong de so sanh khoang cach
for i = 2 : length(tra_x)
    slope(i) = atan((tra_y(i)-tra_y(i-1))/(tra_x(i)-tra_x(i-1))); % Tinh goc nghieng a = tan alpha
  if ((tra_x(i)-tra_x(i-1)) < 0)
      slope(i) = pi + slope(i);
  end
  if (slope(i) > pi)
      slope(i) = slope(i) - 2*pi;
  elseif (slope(i) < -pi)
      slope(i) = slope(i) + 2*pi;
  end
  %if (slope(i) < 0)
  %    slope(i) = slope(i) + 2*pi;
  %end
end
for i = 1: length(tra_x)
   d(i) = sqrt((init_pos(1)-tra_x(i))^2 + (init_pos(2)-tra_y(i))^2);
   % Khoang cach duoc tinh tu diem xuat phat den tat ca cac diem trong quy
   % dao
end
[~, i_min] = min(d); % Tim ra vi tri co khoang cach ngan nhat
start_index = i_min(1);