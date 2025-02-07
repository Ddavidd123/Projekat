# Simulacija Kočenja sa i bez ABS-a

## Pregled
Ovaj program simulira kočenje vozila u različitim uslovima puta, kako sa tako i bez sistema za sprečavanje blokiranja točkova (ABS). 
Program omogućava korisnicima da unesu osnovne parametre kao što su početna brzina vozila, kočiona sila, masa vozila i uslovi puta (tip podloge). 
Simulacija računa udaljenost zaustavljanja, vreme zaustavljanja i daje informacije o eventualnim problemima sa blokiranim točkovima.

## Funkcionalnosti
- **Simulacija kočenja bez ABS-a**: Izračunava udaljenost potrebnu za zaustavljanje vozila na osnovu početne brzine i sile kočenja.
- Ako je kočiona sila veća od maksimalne sile trenja, točkovi se blokiraju i vozilo proklizava.
- **Simulacija kočenja sa ABS-om**: Izračunava isto kao prethodna simulacija, ali sa dinamičkom prilagodom kočione sile da bi se sprečilo blokiranje točkova.
- ABS sistem periodično "otpušta" i "steže" kočnice kako bi održao optimalno prijanjanje točkova.

## Uslovi Puta
Korisnik može da izabere jedan od sledećih uslova puta:
1. **Suv asfalt** (koeficijent trenja: 0.9)
2. **Mokar asfalt** (koeficijent trenja: 0.5)
3. **Sneg/led** (koeficijent trenja: 0.2)

## Parametri Simulacije
Korisnik mora da unese sledeće parametre:
- Početna brzina vozila (u km/h)
- Kočionu silu (u N)
- Masu vozila (u kg)

## Detalji o Izračunima
- **Brzina** se konvertuje iz km/h u m/s.
- **Deceleracija** je izračunata na osnovu koeficijenta trenja i gravitacije.
- **Put kočenja** se računa pomoću formule:  
  \[
  d = \frac{v^2}{2a}
  \]
  gde je \(v\) početna brzina, a \(a\) je ubrzanje (deceleracija).
- **Vreme zaustavljanja** se računa kao:
  \[
  t = \frac{v}{a}
  \]
  gde je \(t\) vreme zaustavljanja.

## Kako koristiti
1. Pokrenite program.
2. Unesite parametre: početnu brzinu vozila, kočionu silu i masu vozila.
3. Izaberite tip podloge.
4. Izaberite tip simulacije (sa ili bez ABS-a).
5. Program će prikazati rezultate simulacije, uključujući ukupnu pređenu distancu i vreme zaustavljanja,
6. kao i obaveštenja o blokiranim točkovima (ako je primenljivo).

   Testiranje Senzora
Program takođe omogućava testiranje senzora temperature koji generiše slučajne uzorke temperature u opsegu od -40°C do 125°C. Testiranje uključuje:

Validaciju podataka: Svaka očitana vrednost temperature se validira da li je unutar dozvoljenog opsega.
Detekcija anomalija: Program detektuje potencijalne anomalije na osnovu razlike u temperaturama između prethodnog i trenutnog uzorka. Ako razlika premaši 80°C, generiše upozorenje o mogućoj anomaliji.
Upis rezultata u fajl: Program upisuje rezultate testiranja, uključujući temperaturu, validnost podatka i da li je detektovana anomalija, u fajl sensor.txt.
