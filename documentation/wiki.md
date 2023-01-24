# Treat Buddy

### System architecture

### Activty diagram

Iz dijagrama aktivnosti možemo vidjeti kako izgleda primarna funkcionalnost TreatBuddy-a koji nakon što pas zalaje će provjeriti je li pas u blizini i ako jeste ispustiti mu hranu.
Nakon što se hrana ispusti uređaj ulazi u deep sleep na određeno vrijeme kako bi uštedio energiju.
[![Activity diagram](https://github.com/khajdinja20/ESD-DogFeeder/blob/master-docs/documentation/pictures/activity%20diagram.jpg)](https://github.com/khajdinja20/ESD-DogFeeder/blob/master-docs/documentation/pictures/activity%20diagram.jpg)

### Comunication diagram

Iz komunikacijskog dijagrama možemo vidjeti kako ESP32 komunicira sa korištenim senzorima.
[![Comunication diagram](https://github.com/khajdinja20/ESD-DogFeeder/blob/master-docs/documentation/pictures/comunication%20diagram.jpg)](https://github.com/khajdinja20/ESD-DogFeeder/blob/master-docs/documentation/pictures/comunication%20diagram.jpg)

### Fritzing


### Troškovnik i financijska analiza
[![financijePUS](https://github.com/khajdinja20/ESD-DogFeeder/blob/main/documentation/pictures/financijePUS.png)

Prema prethodno navedenom troškovniku, ukupna cijena proizvodnje jednog „DogFeeder“ uređaja je 58,39 €. Dasduino mikrokontroler je glavna komponenta uređaja, te prema današnjim cijenama nalazi se oko 15,79 €. Servo motor odgovoran za sipanje psečje hrane u zdjelicu mora biti prilagođen za teži volumen, te je izabran jači servo u te potrebe. Posuda za pse, kao i držač za psečju hranu koji korisnik može napuniti po potrebi dolaze uz sam uređaj, te cijenovno iznose 12,50 €. Izabran je nešto kvalitetniji mikrofon/zvučni senzor zbog potrebe boljeg prepoznavanja lajanja od strane umjetne inteligencije. Za cijelo pakiranje ugrađenog sustava cijenovno se predviđa oko 10,00 €, te je veličine prosječnog kuhala za kavu.
Prema podacima istraživanja , 45% prodanih pametnih hranilica za životinje su bile one s kapacitetom više od 5 litara, te je prema tome kapacitet naše hranilice 6 litara. Također, dodatna prednost je sve veća popularnost consumer IoT uređaja i pametnih domova, što daje veći poticaj vlasnicima ljubimaca da nabave pametne hranilice, pogotovo ako uzmemo u obzir da su mnogo ljudi tijekom pandemije postali vlasnici ljubimaca. 
Nakon analize konkurentskih cijena, naša pametna hranilica za pse prodavala bi se po cijeni od 65,00 €. Smatramo da je to solidna cijena za konkuriranje na tržištu, te uz dodatne napore vezane uz marketing možemo ostvariti pozitivan postotak ROI u dovoljno kratko vrijeme.

### Korisnička dokumentacija
#### Instalacija uređaja
Uređaj izvadite iz pakiranja i priključite u struju. Uređaj radi po „Plug and play“ principu, te nije potrebno dodatno ažuriranje i instalacija. Uređaj, kada je priključen u struju koristi 1 W.
#### Punjenje spremnika za hranu
Na vrhu uređaja nalazi se poklopac koji otvara spremnik u koji je potrebno nasipati pseću hranu. Koristite suhu pseću hranu s manjim komadićima kako bi spriječili potencijalno zaglavljivanje mehanizma za sipanje hrane. Nakon punjenja, vratite poklopac na vrh uređaja i čvrsto zatvorite.
#### Prepoznavanje ljubimca i sipanje hrane
Prije upotrebe uređaja za automatsko sipanje hrane, potrebno je ispod mehanizma za sipanje hrane postaviti zdjelicu za pse. U pakiranju je uključena zdjelica prikladne mjere, no moguće je koristiti bilo koju drugu zdjelicu prikladne veličine. 
Kako bi započeo proces sipanja hrane, ljubimca je potrebno naučiti da se pozicioniraju ispred senzora uređaja koji se nalazi iznad mehanizma za sipanje hrane. Kada ljubimac, to jest pas, zalaje, uređaj će mikrofonom snimiti zvuk i preko umjetne inteligencije prepoznati da se radi o lajanju psa, te će se mehanizam sipanja hrane aktivirati i posipati određenu količinu pseće hrane. Uređaj će zatim ući u stanje dubokog spavanja, u kojem će ostati do sljedećeg definiranog vremena za hranjenje. Zadano vrijeme za duboko spavanje je 4 sata.
#### Čišćenje spremnika
Spremnik za spremanje pseće hrane moguće je preko vrha uređaja izvaditi iz uređaja u potrebe čišćenja. Molimo za sigurnost Vaših ljubimaca temeljito i često čistite spremnik. 
#### Stanja LED diode
Uređaj sadrži LED diodu koja označuje trenutno stanje uređaja. Prilikom priključivanja, uređaj izvršava „Self test“, te LED dioda će zasvijetliti crveno, zeleno te plavo. 
Kada se nešto prepozna ispred senzora, LED dioda će zasvijetliti plavo. Prilikom prepoznavanja lajanja psa LED dioda će zatitrati plavo, što prethodi aktiviranju mehanizma za sipanje hrane.

