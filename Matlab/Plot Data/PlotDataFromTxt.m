fileID = fopen('C:\Users\Duytan2804\Documents\Du lieu bay\30_5_2-1.TXT');
C = textscan(fileID, '%q', 'Delimiter', '\n');
traject_X = [106.76362516667 106.7626541666 106.76166 106.7627353333 106.76362516667];
traject_Y = [10.76957566667 10.77067716667 10.769875 10.76866083333 10.76957566667];
fclose(fileID);
length_C = length(C{1,1});
k = 1;
C1 = [];
C2 = [];
for i = 1 : length_C
    C1{i} = textscan(C{1,1}{i,1}, '%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f', 'Delimiter', ' ');
    if (~isempty(C1{1,i}{1,1}))
        C2{k} = C1{i};
        k = k + 1;
    end
end
length_C2 = length(C2);
m = 1;
C3 = [];
T = [];
Y1 = []; Y2 = []; Y3 = []; Y4 = []; Y5 = []; Y6 =[]; Y7 = []; Y8 = []; Y9 = []; Y10 = []; Y11 = []; Y12 = []; Y13 = []; YD = []; Y15 = [];
for i = 1 : length_C2
    for j = 1 : 17
        if (j == 1)
            m = 1;
        end
        if (~isnan(C2{1,i}{1,j}) & (m < 13))
            C3{i, m} = C2{1,i}{1,j}; 
            m = m + 1;
        end
    end
    C3{i, 2} = (C3{i, 2} - 200)*2/800 - 1;
    C3{i, 3} = (C3{i, 3} - 200)*2/800 - 1;
    T{i} = 0.1 * (i - 1);
    Y1{i} = C3{i, 1}; Y2{i} = C3{i, 2};
    Y3{i} = C3{i, 3}; Y4{i} = C3{i, 4};
    Y5{i} = C3{i, 5}; Y6{i} = C3{i, 6};
    Y7{i} = C3{i, 7}; Y8{i} = C3{i, 8};
    YD{i} = C3{i, 8} - C3{i, 7};
    Y9{i} = C3{i, 9}; Y10{i} = C3{i, 10};
    Y11{i} = C3{i, 11};
    if Y11{i} == 0
        Y11{i} = Y11{i - 1};
    end
    Y12{i} = C3{i, 12};
    if isempty(Y12{i})
        Y12{i} = 10;
    end
    Y12{i} = mod(Y12{i}, 4);
    Y13{i} = Y7{i} - Y8{i};
    Y15{i} = -6.0;
end
plot(cell2mat(T'), cell2mat(Y1)); 
hold on
plot(cell2mat(T'), cell2mat(Y4)); % Roll va Setpoint
hold off
figure;
plot(cell2mat(T'), cell2mat(Y2)); figure; % 
plot(cell2mat(T'), cell2mat(Y3)); figure;
plot(cell2mat(T'), cell2mat(Y5));
hold on
plot(cell2mat(T'), cell2mat(Y15));
hold off
figure;
plot(cell2mat(T'), cell2mat(Y6)); figure;
plot(cell2mat(T'), cell2mat(Y7)); 
hold on
plot(cell2mat(T'), cell2mat(Y8)); 
hold off
figure;
plot(cell2mat(T'), cell2mat(Y13)); figure;
length_Y9 = length(Y9);
for i = 1 : length_Y9
    a = round(Y9{i} / 100);
    b = Y9{i} - a*100;
    Y9{i} = a + b / 60;
    a = round(Y10{i} / 100);
    b = Y10{i} - a*100;
    Y10{i} = a + b / 60;
end
plot(cell2mat(Y10), cell2mat(Y9));
hold on
plot(traject_X, traject_Y);
figure;
scatter(cell2mat(T'), cell2mat(Y11), 'filled');
figure;
scatter(cell2mat(T'), cell2mat(Y12), 'filled');