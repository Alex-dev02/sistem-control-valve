# Code review

## 2022-07-22

### Code structure

- [x] rename pe executabile sa-thermostat, sa-valve
- [x] de vreme ce ai folosit directoare separate fă biblioteci separate pentru fiecare folder (networking)
- [x] folosește Include paths (vezi de exemplu acest [item din SO](https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake)).
- [x] folosește naming consecvent pentru fișiere. Litere mici, și pentru fișiere și pentru directoare.
- [ ] include doar ce e necesar. Include minimul necesar în headere - include doar ce ai nevoie în fiecare unitate de compilare.
- [ ] Functia care extrage variabilele din request trebuie regandita

### Valve/Thermostat

- [x] termostatul crash-uieste daca primeste requesturi in care variabilele sunt numite incorect
- [x] ce se intampla daca primim o variabila fara valoare in path + unit test pe ea
- [ ] `void SetTemperature(float temperature);` și `void IncrementTemperature();` sunt publice. De ce?
- [ ] Îmi e neclară relația dintre clasa Valve și clasa Router. Valva este un Router? Are un router? Ar trebui să fie derivată din Router?
- [ ] Pentru Router este un tip de date complex ar trebui să nu poată fi copiat - operațiunea de copiere nu ar trebui să aibă sens pentru Router. Tu faci o copie în main, dar dacă adaug on-the-fly noi endpoints în Router? `main` nu le va vedea.
- [ ] main-ul de la termostat și valvă seamănă foarte mult. Se poate refolosi acel cod?
- [ ] Thermostat::SetTarget are prea multe responsabilități. Face parsare de date, actualizare de structuri interne, management de stream-uri de rețea, compunere de mesaje și trimitere de mesaje, compunere de răspunsuri.
- [x] typo: „Coulnd not”
- [ ] Too many things are included in the main of thermostat
- [ ] What would it take to have the valve threads done in only one thread? How about doing it in the main thread?
- [ ] remove la valve ar trebui sa se realizeze pe baza ip-ului


### Networking

- [ ] GetStream ar trebui să returneze un stream, nu un int.
- [ ] Porturile sunt uint16_t. Nu string, nu altceva.
- [x] `IsResponseASuccess` should be `Successful`

### Features

- [x] input validator pentru requesturi HTTP si IotDCP poate
- [ ] logger (single tone)
- [ ] polling de la valve la thermostat -> daca nu mai raspunde termostatul atunci revenim la o valoare default ca target al valvelor
- [ ] unit teste
- [ ] valva sa primeasca requesturi http ca sa stie care ii este thermostatul (? de discutat deoarece momentan se intampla invers)
- [ ] nu ar trebui sa putem inregistra o valva daca nu e pornita
- [ ] folosire json pentru interpretari de request/response
- [ ] folosire stl petru operatii de cautare/stergere etc

### FIXES 

- [ ] de ce trebuiesc adaugate iar pathurile in router la RouterTest.cpp
- [x] foloseste try catch pentru apelarea Request::GetPathVar, eventual o functie care sa faca try catchul
