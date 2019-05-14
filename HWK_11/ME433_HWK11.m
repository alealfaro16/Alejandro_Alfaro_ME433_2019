
%Gains to achieve cut-off frequency of 5Hz
%freqz([1/9,1/9,1/9,1/9,1/9,1/9,1/9,1/9,1/9]); %MAF
%freqz(2/5,3/5); %IIR
%fir1(4,0.1) %FIR
%freqz(a,b,c,d,e)

port = '/dev/tty.usbmodem14101';
data = zeros(100,5);
data_t = zeros(100,3);

if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
ser = serial(port,'BaudRate',230400);
fopen(ser);

fprintf(ser,'%c\n',114);
for i = 1:100
   data(i,:) = fscanf(ser,"%d  %d  %d  %f  %f");
   %data_t(i,:) = fscanf(ser,"%d  %d  %d");
end

x = data(:,1);
z_raw = data(:,2);
z_MAF = data(:,3);
z_IIR = data(:,4);
z_FIR = data(:,5);


plot(x,z_raw) 
hold on 
xlabel('Sample Number')
ylabel('Z value')
plot(x,z_MAF)
plot(x,z_IIR)
plot(x,z_FIR)
hold off
legend('Raw','MAF','IIR','FIR')


fclose(ser);