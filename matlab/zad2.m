% skrypt tworzy dwa sygna³y okresowe (sin i cos)
% i oblicza ich sumy

% Dane wejsciowe
Tk = 1;           % czas trwania sygna³u w sekundach
fs = 1000;         % czesttliwosc. próbkowania w [Hz]
f1 = 2;           % czestotliwosc pierwszego sygna³u
f2 = 10;          % czestotliwosc drugiego sygna³u
A1 = 1;A2 = 1;  % aplitudy sygna³ów

dt = 1/fs;        %okres probkowania
t  = 0:dt:Tk-dt;     % wektor czasu dyskretnego

s1 = A1*sin(2*pi*f1*t); % sygnal 1


s2 = [];                % sygnal 2
probes  = ceil(fs/f2/2) % ilosc probek potrzebnych do wygenerowania polowy
                        % okresu, poniewaz okres sklada sie z 1 i -1 
for period =1:(f2+1)    % wygeneruj o okres wiecej, ulatwia obliczenia
  s2 = [ s2,      A2*ones(1,probes) ];  % generuj  1
  s2 = [ s2, (-1)*A2*ones(1,probes) ];  % generuj -1
end
s2 = s2(1:fs);

sygnal = s1 + s2;       % suma sygnalow
X =  fft(sygnal);        % fft dla s1+ s2
x_amplitude = abs(X);    % wartosci prazkow

subplot(3,1,1)          % wykres sygnal 1
plot(t, s1)
grid on
title('Sygnal 1.')
xlabel('Czas [s]')
ylabel('[V]')

subplot(3,1,2)          % wykres sygnal 2
plot(t, s2)
grid on
title('Sygnal 2.')
xlabel('Czas [s]')
ylabel('[V]')

subplot(3,1,3)          % wykres sygnal suma
plot(t, sygnal)
grid on
title('Suma sygnalow s1 i s2.')
xlabel('Czas [s]')
ylabel('[V]')

figure
plot(t, x_amplitude)
title('Suma sygnalow s1 i s2.')
xlabel('Czas [s]')
ylabel('[V]')