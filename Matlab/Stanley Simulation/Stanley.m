%% Desired parameters
tra_x = [0 0 2 3];
tra_y = [0 1 2 5];
%tra_y = [14 17 18 21 19 17 15 12 10 7 6 4 3 0];
init_pos = [2 0];
init_angle = 1.56;
plot(tra_x, tra_y);
slope = [];   %Tao mang trong cho du lieu goc nghieng a     
d = [];    % Tao mang trong de so sanh khoang cach
for i = 2 : length(tra_x)
    slope(i) = atan((tra_y(i)-tra_y(i-1))/(tra_x(i)-tra_x(i-1))); % Tinh goc nghieng a = tan alpha
  if ((tra_x(i)-tra_x(i-1)) < 0)
      slope(i) = pi + slope(i);
  end
  if (slope(i) < 0)
      slope(i) = slope(i) + 2*pi;
  end
end
for i = 1: length(tra_x)
   d(i) = sqrt((init_pos(1)-tra_x(i))^2 + (init_pos(2)-tra_y(i))^2);
   % Khoang cach duoc tinh tu diem xuat phat den tat ca cac diem trong quy
   % dao
end
[~, i_min] = min(d); % Tim ra vi tri co khoang cach ngan nhat
start_index = i_min(1);