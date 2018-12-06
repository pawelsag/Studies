%projektowanie filtru cyfrowego FIR
% metoda probkowania w dziedzinie czestotliowsci
% okno = 0 - bez okna(okno prostokatnme); okno = 1 -okno Blackmana
clf; clear all; subplot(1,1,1)
N = 33;    %dlugosc odp. impulsowej = rzad filtru(liczba nieparzysta)
%odpowiedz impulsowa symetryczna - TypI
okno =0; % bez okna(okno prosokatne)
%okno = 1 % z oknem (Blackmana)
M = (N-1)/2;
M2 = M/2; % 0.25 rzedu filtru 
z2 = zeros(1,M2);j2 = ones(1,M2);
Ar = [1 j2 z2 z2 j2]; % czesc rzeczywista idelanej charaktersytki
Ai = zeros(1,N);   % czesc urojona
A = Ar + j*Ai;    % zespolona funkcja transmitancji
% obliczenie IDFT{A} === >> h(n)

n = 0:(N-1);

f = n/N;   % czestotliwosc unormowana
h = zeros(1,N);

for k = 0:(N-1)
    h = h+A(k+1)*exp(j*2*pi*k/N*(n-M) ) ;
    %  n-M przesuniecie kolowe o M probek w prawo
end

subplot(3,2,1)
stem( (n-M), h, '.' ); grid on;
title('Odpowiedz impulsowa filtru h(n)' )
% ===== liczenie dft z h(n)
NF = 1000;   % liczba probke tranmitancji filtru
k = 0:NF-1;  % indeksy dla kolejnych czestotliowsci
fn = k/NF;   % czestotliowsc unormowana
for k =0:NF-1
    H(k+1)=exp(-j*2*pi*k/NF*(n-N))*h';
end

H=H/N;
Hx =real(H);

subplot(3,2,3)
stem(f,Ar,'r');grid on;
hold on;
plot(fn,abs(H),'b');
%plot(f,Ar,'r',fn,abs(H),'b');grid on;
title('Charakterystyki ampl. filtru: idealna i faktyczna')
legend('idealna','faktyczna')


subplot(3,2,5)
plot(fn,20*log10( abs(H) )); grid on;
title('abs(H) w [dB]');


% zastosowanie f.okna do odp.impulsowej
h= h.*blackman(N)';
subplot(3,2,2)
stem( (n-M), h, '.' ); grid on;
title('Odpowiedz impulsowa filtru h(n)[Blackman]' )

for k =0:NF-1
    H(k+1)=exp(- j*2*pi*k/NF*(n-N) )*h';
end

H=H/N;
Hx =real(H);

subplot(3,2,4)
stem(f,Ar,'r');grid on;
hold on;
plot(fn,abs(H),'b');
title('Charakterystyki ampl. filtru: idealna i faktyczna[Blackman]')
legend('idealna','faktyczna')


subplot(3,2,6)
plot(fn,20*log10( abs(H) )); grid on;
title('abs(H) w [dB][Blackman]');

% zadanie domowe
% wymnozyc h(n) przez okno Blackmana
% i powtorzyc obliczenia funkcji tranmitancji
% dla zokienkowanej odpowiedzi impulsowej